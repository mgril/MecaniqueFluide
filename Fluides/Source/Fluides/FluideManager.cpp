// Fill out your copyright notice in the Description page of Project Settings.


#include "FluideManager.h"

// Sets default values
AFluideManager::AFluideManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
}

// Called when the game starts or when spawned
void AFluideManager::BeginPlay()
{
	Super::BeginPlay();

    if (bDebugDrawBounds)
    {
        const FVector Center = (BoundsMin + BoundsMax) * 0.5f;
        const FVector Extents = (BoundsMax - BoundsMin) * 0.5f;
        DrawDebugBox(GetWorld(), Center, Extents,
            FColor::Cyan, true, -1.f, 0, 2.f);
    }
    FluidISMs.SetNum(Fluids.Num());
    for (int32 f = 0; f < Fluids.Num(); ++f)
    {
        // Create one ism per fluid
        FName Name = FName(*FString::Printf(TEXT("FluidISM_%d"), f));
        UInstancedStaticMeshComponent* ISM =
            NewObject<UInstancedStaticMeshComponent>(this, Name);

        ISM->SetupAttachment(RootComponent);
        ISM->RegisterComponent();
        ISM->SetMobility(EComponentMobility::Movable);
        ISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        ISM->SetGenerateOverlapEvents(false);
        ISM->bReceivesDecals = false;
        ISM->CastShadow = false;

        if (ParticleStaticMesh)       ISM->SetStaticMesh(ParticleStaticMesh);
        if (Fluids[f].Material)       ISM->SetMaterial(0, Fluids[f].Material);

        FluidISMs[f] = ISM;

        InitFluid(f);
    }

	
}
// Called every frame
void AFluideManager::InitFluid(int32 FluidIdx)
{
    FFluid& Fluid = Fluids[FluidIdx];

    //Mass per prtc
    const FVector BoxSize = BoundsMax - BoundsMin; // cm 
    const float ContentVolum = BoxSize.X * BoxSize.Z * Fluid.InfluenceRadius; // cm 3
    Fluid.Mass =  (ContentVolum * Fluid.RestDensity) / FMath::Max(Fluid.NumParticles, 1);

    for (int32 i = 0; i < Fluid.NumParticles; ++i)
    {
        // Random in bounds (plan XZ pour le 2D, Y=0)
        FVector Pos = FVector(
            FMath::RandRange(BoundsMin.X, BoundsMax.X),
            0.f,
            FMath::RandRange(BoundsMin.Z, BoundsMax.Z)
        );

        FFluidParticle P;
        P.Position = Pos;
        P.Velocity = FVector::ZeroVector;
        P.Force = FVector::ZeroVector;
        P.Density = Fluid.RestDensity;
        P.Pressure = 0.f;
        P.FluidIndex = FluidIdx;

        Particles.Add(P);

        FTransform T;
        T.SetLocation(Pos);
        T.SetScale3D(ParticleScale);
        FluidISMs[FluidIdx]->AddInstance(T);
    }
}

void AFluideManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Fluids.Num() == 0 || Particles.Num() == 0) return;
    // Log pendant les 3 premières frames seulement
    static int32 FrameCount = 0;
    //if (FrameCount < 3)
    //{
    //    float MinD = FLT_MAX, MaxD = -FLT_MAX, AvgD = 0.f;
    //    float MinP = FLT_MAX, MaxP = -FLT_MAX;
    //    float MinF = FLT_MAX, MaxF = -FLT_MAX;

    //    for (auto& P : Particles)
    //    {
    //        MinD = FMath::Min(MinD, P.Density);
    //        MaxD = FMath::Max(MaxD, P.Density);
    //        AvgD += P.Density;
    //        MinP = FMath::Min(MinP, P.Pressure);
    //        MaxP = FMath::Max(MaxP, P.Pressure);
    //        MinF = FMath::Min(MinF, P.Force.Size());
    //        MaxF = FMath::Max(MaxF, P.Force.Size());
    //    }
    //    AvgD /= Particles.Num();

    //    UE_LOG(LogTemp, Warning,
    //        TEXT("=== FRAME %d ==="), FrameCount);
    //    UE_LOG(LogTemp, Warning,
    //        TEXT("Density  min=%.6f  max=%.6f  avg=%.6f  | RestDensity[0]=%.6f"),
    //        MinD, MaxD, AvgD, Fluids[0].RestDensity);
    //    UE_LOG(LogTemp, Warning,
    //        TEXT("Pressure min=%.2f  max=%.2f"),
    //        MinP, MaxP);
    //    UE_LOG(LogTemp, Warning,
    //        TEXT("Force    min=%.2f  max=%.2f  | Gravity=%.2f"),
    //        MinF, MaxF, Gravity.Z);
    //    UE_LOG(LogTemp, Warning,
    //        TEXT("Mass[0]=%.8f | h[0]=%.2f"),
    //        Fluids[0].Mass, Fluids[0].InfluenceRadius);

    //    ++FrameCount;
    //}
    ComputeDensity();
    ComputePressure();
    ComputeForces();
    Integrate(DeltaTime);
    HandleBounds();
    UpdateInstances();

}

// KERNELS 

float AFluideManager::Poly6Kernel(float r, float h)
{
    // W(r,h) = (315 / 64PIh^9) * (h^2 - r^2)^3 voir pdf 13 to 15
    if (r > h) return 0.f;

    const float Coeff = 315.f / (64.f * PI * FMath::Pow(h, 9));
    const float Val = (h * h) - (r * r);
    return Coeff * Val * Val * Val;
}


float AFluideManager::SpikyKernelDerivative(float r, float h) // gradient de pression voir pdf p 44
{
    // dSpiky = -(45 / PIh^6) * (h - r)^2
    if (r > h || r <= 0.f) return 0.f;

    const float Coeff = -45.f / (PI * FMath::Pow(h, 6));
    const float Val = (h - r);
    return Coeff * Val * Val;
}
float AFluideManager::GetCrossPressureFactor(int32 A, int32 B) const
{
    if (A == B) return 1.f;
    // Moyenne geometrique : plus stable que la moyenne arithmetique
    // pour des facteurs très différents (ex: 1.0 et 5.0)
    return FMath::Sqrt(Fluids[A].CrossPressureFactor
                     * Fluids[B].CrossPressureFactor);
}
float AFluideManager::GetCrossViscosityFactor(int32 A, int32 B) const
{
    if (A == B) return 1.f;
    return FMath::Sqrt(Fluids[A].CrossViscosityFactor
        * Fluids[B].CrossViscosityFactor);
}
void AFluideManager::ComputeDensity()
{
    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        float Density = 0.f;
        const float hi = Fluids[Particles[i].FluidIndex].InfluenceRadius;

        for (int32 j = 0; j < Particles.Num(); ++j)
        {
            const float hj = Fluids[Particles[j].FluidIndex].InfluenceRadius;
            const float hEff = (hi + hj) * 0.5f;

            const float DistM = (Particles[i].Position - Particles[j].Position).Size();

            Density += Fluids[Particles[j].FluidIndex].Mass
                * Poly6Kernel(DistM, hEff);
        }

        // / 0 imposs
        const float MinDensity = Fluids[Particles[i].FluidIndex].RestDensity * 0.01f;
        Particles[i].Density = FMath::Max(Density, MinDensity);
    }
}
void AFluideManager::ComputePressure()
{
    for (FFluidParticle& P : Particles)
    {
        const FFluid& F = Fluids[P.FluidIndex];
        const float Ratio = P.Density / F.RestDensity;
        P.Pressure = F.TaitK * (FMath::Pow(Ratio, 7.f) - 1.f);
    }
}
void AFluideManager::ComputeForces()
{
    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        const int32   Fi = Particles[i].FluidIndex;
        const float   hi = Fluids[Fi].InfluenceRadius;

        FVector PressureForce = FVector::ZeroVector;
        FVector ViscosityForce = FVector::ZeroVector;

        for (int32 j = 0; j < Particles.Num(); ++j)
        {
            if (i == j) continue;

            const int32 Fj = Particles[j].FluidIndex;
            const float hj = Fluids[Fj].InfluenceRadius;
            const float hEff = (hi + hj) * 0.5f;

            const FVector DirCm = Particles[i].Position - Particles[j].Position;
            const float   Dist = DirCm.Size();

            if (Dist <= 0.f || Dist > hEff) continue;

            const FVector UnitDir = DirCm.GetSafeNormal();
            const float   dW = SpikyKernelDerivative(Dist, hEff);

            //    Pression
            const float CrossP = GetCrossPressureFactor(Fi, Fj);

            const float PressureTerm = CrossP * Fluids[Fj].Mass
                * (Particles[i].Pressure / FMath::Square(Particles[i].Density)
                    + Particles[j].Pressure / FMath::Square(Particles[j].Density));

            PressureForce -= PressureTerm * dW * UnitDir;

            //    Viscosité 
            // µ effectif = moyenne des viscosités * facteur cross
            const float CrossV = GetCrossViscosityFactor(Fi, Fj);
            const float MuEff = (Fluids[Fi].Viscosity + Fluids[Fj].Viscosity)
                * 0.5f * CrossV;

            const FVector VelDiff = Particles[j].Velocity - Particles[i].Velocity;
            const float   Denom = Dist * Dist + 0.01f * hEff * hEff;
            const float   ViscTerm = (Fluids[Fj].Mass / Particles[j].Density)
                * (dW * Dist / Denom);

            ViscosityForce += 2.f * MuEff * ViscTerm * VelDiff;
        }

        // Gravity — accélération directe (pas de /masse car deja en cm/s^2)
        Particles[i].Force = (PressureForce / Particles[i].Density)
            + ViscosityForce
            + Gravity;
    }
}

void AFluideManager::Integrate(float DeltaTime)
{
    for (FFluidParticle& P : Particles)
    {
        // Force ici = accélération (m/s^2)
        P.Velocity += P.Force * DeltaTime;
        P.Velocity.Y = 0.f;                        // verrouille Y (2D)

        // est ce que la velocite dans unreal est en m/s ou cm par seconde ?????? si m / s il mnque un *100
        P.Position += P.Velocity * DeltaTime ;
        P.Position.Y = 0.f;
    }
}

void AFluideManager::HandleBounds()
{
    for (FFluidParticle& P : Particles)
    {
        if (P.Position.X < BoundsMin.X)
        {
            P.Position.X = BoundsMin.X; P.Velocity.X *= -BoundsDamping;
        }
        if (P.Position.X > BoundsMax.X)
        {
            P.Position.X = BoundsMax.X; P.Velocity.X *= -BoundsDamping;
        }
        if (P.Position.Z < BoundsMin.Z)
        {
            P.Position.Z = BoundsMin.Z; P.Velocity.Z *= -BoundsDamping;
        }
        if (P.Position.Z > BoundsMax.Z)
        {
            P.Position.Z = BoundsMax.Z; P.Velocity.Z *= -BoundsDamping;
        }
    }
}

void AFluideManager::UpdateInstances()
{
    // Compteur d'instance local par fluide
    TArray<int32> InstanceCounters;
    InstanceCounters.SetNumZeroed(Fluids.Num());

    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        const int32 f = Particles[i].FluidIndex;
        const int32 ii = InstanceCounters[f]++;

        FTransform T;
        T.SetLocation(Particles[i].Position);
        T.SetScale3D(ParticleScale);

        const bool bMarkRenderDirty =
            (ii == FluidISMs[f]->GetInstanceCount() - 1);

        FluidISMs[f]->UpdateInstanceTransform(ii, T, false, bMarkRenderDirty);
    }
}


