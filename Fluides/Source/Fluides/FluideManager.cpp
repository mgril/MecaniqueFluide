// Fill out your copyright notice in the Description page of Project Settings.


#include "FluideManager.h"

// Sets default values
AFluideManager::AFluideManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
}


void AFluideManager::BeginPlay()
{
	Super::BeginPlay();

    if (bDebugDrawBounds)
    {
        const FVector Center = (BoundsMin + BoundsMax) * 0.5f *100.f;       //  *100.f conversion en cm pour unreal 
        const FVector Extents = (BoundsMax - BoundsMin) * 0.5f * 100.f;     //  *100.f conversion en cm pour unreal 
        DrawDebugBox(GetWorld(), Center, Extents,
            FColor::Cyan, true, -1.f, 0, 2.f);
    }

    FluidISMs.SetNum(Fluids.Num());
    for (int32 f = 0; f < Fluids.Num(); ++f)
    {
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
        ISM->SetCullDistances(0, 0);

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

    ////Mass per prtc
    const FVector BoxSize = BoundsMax - BoundsMin; // m 
    const float Volum = BoxSize.X * BoxSize.Z * ParticleScale.X ; // m3
    const float Spacing = FMath::Sqrt(Volum / FMath::Max(Fluid.NumParticles, 1));
    //Fluid.Mass = (Volum * Fluid.RestDensity) / FMath::Max(Fluid.NumParticles, 1);
    Fluid.InfluenceRadius = Spacing * Fluid.InfluenceRadius;
    const float h = Fluid.InfluenceRadius;

    // SumW = somme réelle du kernel sur tous les voisins de grille
    float SumW = 0.f;
    for (int32 dx = -2; dx <= 2; ++dx)
        for (int32 dz = -2; dz <= 2; ++dz)
        {
            const float Dist = FMath::Sqrt((float)(dx * dx + dz * dz)) * Spacing;
            if (Dist < h)
                SumW += Poly6Kernel(Dist, h);
        }

    Fluid.Mass = (SumW > 0.f )
        ? Fluid.RestDensity / SumW
        : 1.f;

    // ---  Spawn en grille couvrant toute la boite ---------------------------
    const int32 Cols = FMath::CeilToInt(FMath::Sqrt((float)Fluid.NumParticles));
    const int32 Rows = FMath::CeilToInt((float)Fluid.NumParticles / Cols);
    // Espacement adapté pour couvrir toute la boîte
    // On répartit les particules uniformément sur X et Z
    const float StepX = BoxSize.X / Cols;
    const float StepZ = BoxSize.Z / Rows;

    // Première particule à StepX/2 depuis le bord  grille centrée
    const FVector Origin = FVector(
        BoundsMin.X + StepX * 0.5f,
        0.f,
        BoundsMin.Z + StepZ * 0.5f
    ) + Fluid.SpawnOffset;

    int32 Spawned = 0;
    for (int32 row = 0; row < Rows && Spawned < Fluid.NumParticles; ++row)
    {
        for (int32 col = 0; col < Cols && Spawned < Fluid.NumParticles; ++col)
        {
            float NoiseX = FMath::FRandRange(-StepX, StepX) * 0.1f;
            float NoiseZ = FMath::FRandRange(-StepZ, StepZ) * 0.1f;
            FVector Pos = Origin + FVector(col * StepX, 0.f, row * StepZ) + FVector(NoiseX, 0.f, NoiseZ);

            // Sécurité — reste dans les bounds
            Pos.X = FMath::Clamp(Pos.X, BoundsMin.X, BoundsMax.X);
            Pos.Z = FMath::Clamp(Pos.Z, BoundsMin.Z, BoundsMax.Z);


            FFluidParticle P;
            P.Position = Pos;
            P.Velocity = FVector::ZeroVector;
            P.Force = FVector::ZeroVector;
            P.Density = Fluid.RestDensity;
            P.Pressure = 0.f;
            P.FluidIndex = FluidIdx;
            Particles.Add(P);

            FTransform T;
            T.SetLocation(Pos * 100.f);  // m en cm pour Unreal
            T.SetScale3D(ParticleScale);
            FluidISMs[FluidIdx]->AddInstance(T);
            ++Spawned;
        }
    }
}

void AFluideManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Fluids.Num() == 0 || Particles.Num() == 0) return;

    static int32 Frame = 0;
    
    ComputeDensity();
    ComputePressure();
    ComputeForces();
    Integrate(DeltaTime);
    HandleBounds();
    UpdateInstances();

}

// KERNELS 

float AFluideManager::Poly6Kernel(float r, float h)                    // PDF 11-18
{
    // W(r,h) = (315 / 64PIh^9) * (h^2 - r^2)^3
    if (r > h) return 0.f;

    const float Coeff = 315.f / (64.f * PI * FMath::Pow(h, 9));
    const float V = (h * h) - (r * r);
    return Coeff * V * V * V;
}


float AFluideManager::SpikyKernelDerivative(float r, float h)          // PDF 44
{
    // dSpiky = -(45 / PIh^6) * (h - r)^2
    if (r > h || r <= 0.f) return 0.f;

    const float Coeff = -45.f / (PI * FMath::Pow(h, 6));
    const float V = (h - r);
    return Coeff * V * V;
}

void AFluideManager::ComputeDensity()                                  // PDF 22
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

        Particles[i].Density = FMath::Max(Density,
            Fluids[Particles[i].FluidIndex].RestDensity * 0.01f);
    }


}
void AFluideManager::ComputePressure()                                 // PDF 26
{
    for (FFluidParticle& P : Particles)
    {
        const FFluid& F = Fluids[P.FluidIndex];
        const float Ratio = P.Density / F.RestDensity;
        // Max(0)  : pression nulle quand d_i <= d0
        // evite l'attraction qui colle les particules dans les coins // PDF 28
        P.Pressure = FMath::Max(0.f, F.TaitK * (FMath::Pow(Ratio, 7.f) - 1.f));
    }
}
void AFluideManager::ComputeForces()                                   // PDF 49 77 80
{
    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        const int32   Fi = Particles[i].FluidIndex;
        const float   hi = Fluids[Fi].InfluenceRadius;
        const float di = Particles[i].Density;
        const float pi = Particles[i].Pressure;

        FVector PressureForce = FVector::ZeroVector;
        FVector ViscosityForce = FVector::ZeroVector;

        for (int32 j = 0; j < Particles.Num(); ++j)
        {
            if (i == j) continue; 
            const int32 Fj = Particles[j].FluidIndex;
            const float hj = Fluids[Fj].InfluenceRadius;
            const float hEff = (hi + hj) * 0.5f;

            const FVector Dir =Particles[j].Position - Particles[i].Position; 
            const float   Dist = Dir.Size();

            if (Dist <= 0.f || Dist > hEff) continue;

            const FVector UnitDir = Dir / Dist;
            const float   dW = SpikyKernelDerivative(Dist, hEff);
            const float   mj = Fluids[Fj].Mass;
            const float   dj = Particles[j].Density;
            const float   pj = Particles[j].Pressure;

            if (pi <= 0.f && pj <= 0.f) continue;
            // Pression — page 49
            PressureForce -= mj * (pi / (di * di) + pj / (dj * dj))
                * dW * UnitDir;

            // Viscosité — page 77
            const FVector VelDiff = Particles[j].Velocity - Particles[i].Velocity;
            const float   Denom = Dist * Dist + 0.01f * hEff * hEff;
            ViscosityForce += 2.f * (mj / dj) * VelDiff * (dW * Dist / Denom);
        }

        // Total Velocity page 80
        Particles[i].Force = PressureForce 
            + (Fluids[Fi].Viscosity * ViscosityForce / di)
            + Gravity;
    }
}

void AFluideManager::Integrate(float DeltaTime)                        // PDF 80
{
    DeltaTime = FMath::Min(DeltaTime, 0.008f);
    for (FFluidParticle& P : Particles)
    {
        P.Velocity += P.Force * DeltaTime;
        P.Velocity.Y = 0.f;                        // verrouille Y (2D)

        P.Position += P.Velocity * DeltaTime ;
        P.Position.Y = 0.f;                        // verrouille Y (2D)
    }
}

void AFluideManager::HandleBounds()
{
    for (FFluidParticle& P : Particles)
    {
        // Mur gauche
        if (P.Position.X < BoundsMin.X)
        {
            P.Position.X = BoundsMin.X;
            P.Velocity.X = FMath::Abs(P.Velocity.X) * BoundsDamping;
            P.Velocity.Z *= BoundsDamping;  // friction sur la paroi
        }
        // Mur droit
        if (P.Position.X > BoundsMax.X)
        {
            P.Position.X = BoundsMax.X;
            P.Velocity.X = -FMath::Abs(P.Velocity.X) * BoundsDamping;
            P.Velocity.Z *= BoundsDamping;
        }
        // Sol
        if (P.Position.Z < BoundsMin.Z)
        {
            P.Position.Z = BoundsMin.Z;
            P.Velocity.Z = FMath::Abs(P.Velocity.Z) * BoundsDamping;
            P.Velocity.X *= BoundsDamping;  // friction sur le sol
        }
        // Plafond
        if (P.Position.Z > BoundsMax.Z)
        {
            P.Position.Z = BoundsMax.Z;
            P.Velocity.Z = -FMath::Abs(P.Velocity.Z) * BoundsDamping;
            P.Velocity.X *= BoundsDamping;
        }
    }
}

void AFluideManager::UpdateInstances()
{
    TArray<int32> Counters;
    Counters.SetNumZeroed(Fluids.Num());

    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        const int32 f = Particles[i].FluidIndex;
        const int32 ii = Counters[f]++;

        FTransform T;
        T.SetLocation(Particles[i].Position * 100.f);
        T.SetScale3D(ParticleScale);

        const bool bDirty = (ii == FluidISMs[f]->GetInstanceCount() - 1);
        FluidISMs[f]->UpdateInstanceTransform(ii, T, false, bDirty);
    }
}


