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
    FluidInstanceScales.SetNum(Fluids.Num());
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

    ComputeDensity();
    ComputePressure();
    ComputeForces();

    for (int32 Step = 0; Step < WarmupSteps; ++Step)
    {
        Integrate(WarmupStep);
    }

    UpdateInstances();
}
// Called every frame
void AFluideManager::InitFluid(int32 FluidIdx)
{
    FFluid& Fluid = Fluids[FluidIdx];

    ////Mass per prtc
    const FVector BoxSize = BoundsMax - BoundsMin; // m
    const int32 FluidCount = FMath::Max(Fluids.Num(), 1);

    FVector SpawnMin = BoundsMin;
    FVector SpawnMax = BoundsMax;

    if (FluidCount > 1)
    {
        const float LaneWidth = BoxSize.X / FluidCount;
        SpawnMin.X = BoundsMin.X + LaneWidth * FluidIdx;
        SpawnMax.X = SpawnMin.X + LaneWidth;
    }

    SpawnMin += Fluid.SpawnOffset;
    SpawnMax += Fluid.SpawnOffset;

    if (SpawnMin.X < BoundsMin.X)
    {
        const float Shift = BoundsMin.X - SpawnMin.X;
        SpawnMin.X += Shift;
        SpawnMax.X += Shift;
    }
    if (SpawnMax.X > BoundsMax.X)
    {
        const float Shift = SpawnMax.X - BoundsMax.X;
        SpawnMin.X -= Shift;
        SpawnMax.X -= Shift;
    }
    if (SpawnMin.Z < BoundsMin.Z)
    {
        const float Shift = BoundsMin.Z - SpawnMin.Z;
        SpawnMin.Z += Shift;
        SpawnMax.Z += Shift;
    }
    if (SpawnMax.Z > BoundsMax.Z)
    {
        const float Shift = SpawnMax.Z - BoundsMax.Z;
        SpawnMin.Z -= Shift;
        SpawnMax.Z -= Shift;
    }

    const FVector SpawnBoxSize = SpawnMax - SpawnMin;

    // ---  Spawn en grille 2D adaptee au ratio de la zone de spawn ------------
    const float AspectRatio = FMath::Max(SpawnBoxSize.X / FMath::Max(SpawnBoxSize.Z, KINDA_SMALL_NUMBER), KINDA_SMALL_NUMBER);
    const int32 Cols = FMath::Max(1, FMath::CeilToInt(FMath::Sqrt((float)Fluid.NumParticles * AspectRatio)));
    const int32 Rows = FMath::Max(1, FMath::CeilToInt((float)Fluid.NumParticles / Cols));
    const float StepX = SpawnBoxSize.X / Cols;
    const float StepZ = SpawnBoxSize.Z / Rows;
    const float Spacing = (StepX + StepZ) * 0.5f;
    const FVector InstanceScale = bAutoParticleScale
        ? FVector(Spacing * ParticleScaleSpacingRatio)
        : ParticleScale;
    FluidInstanceScales[FluidIdx] = InstanceScale;

    // h est le rayon d'influence en metres, comme dans le cours.
    Fluid.InfluenceRadius = FMath::Max(Fluid.InfluenceRadius, KINDA_SMALL_NUMBER);
    const float h = Fluid.InfluenceRadius;

    // Masse automatique en 2D: densite cible * aire / nombre de particules.
    const float Area = SpawnBoxSize.X * SpawnBoxSize.Z;
    Fluid.Mass = (Fluid.NumParticles > 0)
        ? (Fluid.RestDensity * Area) / Fluid.NumParticles
        : 1.f;

    // Première particule à StepX/2 depuis le bord  grille centrée
    const FVector Origin = FVector(
        BoundsMin.X + StepX * 0.5f,
        0.f,
        BoundsMin.Z + StepZ * 0.5f
    ) + Fluid.SpawnOffset;

    int32 Spawned = 0;
    for (int32 row = 0; row < Rows && Spawned < Fluid.NumParticles; ++row)
    {
        const int32 Remaining = Fluid.NumParticles - Spawned;
        const int32 RowsLeft = Rows - row;
        const int32 CountThisRow = FMath::Min(Cols, FMath::CeilToInt((float)Remaining / RowsLeft));
        const float RowWidth = (CountThisRow - 1) * StepX;
        const float StartX = (SpawnMin.X + SpawnMax.X) * 0.5f - RowWidth * 0.5f;
        const float Stagger = (CountThisRow > 1 && (row % 2) == 1) ? StepX * 0.5f : 0.f;

        for (int32 col = 0; col < CountThisRow && Spawned < Fluid.NumParticles; ++col)
        {
            FVector Pos = FVector(
                StartX + col * StepX + Stagger,
                0.f,
                SpawnMin.Z + StepZ * (row + 0.5f)
            );

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
            T.SetScale3D(InstanceScale);
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
    
    const float SimDeltaTime = FMath::Min(DeltaTime, MaxSimulationStep * MaxSimulationSubsteps);
    const int32 StepCount = FMath::Max(1, FMath::CeilToInt(SimDeltaTime / MaxSimulationStep));
    const float StepDeltaTime = SimDeltaTime / StepCount;

    for (int32 Step = 0; Step < StepCount; ++Step)
    {
        Integrate(StepDeltaTime);
    }

    UpdateInstances();

    if (bDebugFluidValues && ++DebugFrameCounter >= DebugFrameInterval)
    {
        DebugFrameCounter = 0;
        float MinDensity = TNumericLimits<float>::Max();
        float MaxDensity = 0.f;
        float MaxPressure = 0.f;
        float MaxSpeed = 0.f;

        for (const FFluidParticle& P : Particles)
        {
            MinDensity = FMath::Min(MinDensity, P.Density);
            MaxDensity = FMath::Max(MaxDensity, P.Density);
            MaxPressure = FMath::Max(MaxPressure, P.Pressure);
            MaxSpeed = FMath::Max(MaxSpeed, P.Velocity.Size());
        }

        UE_LOG(LogTemp, Log, TEXT("Fluid debug | density %.2f - %.2f | pressure max %.2f | speed max %.2f"),
            MinDensity, MaxDensity, MaxPressure, MaxSpeed);
    }

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
            if (i == j) continue;
            const float hj = Fluids[Particles[j].FluidIndex].InfluenceRadius;
            const float hEff = (hi + hj) * 0.5f;

            const float DistM = (Particles[i].Position - Particles[j].Position).Size();

            Density += Fluids[Particles[j].FluidIndex].Mass
                * Poly6Kernel(DistM, hEff);
        }

        Particles[i].Density = (Density > 0.f)
            ? FMath::Max(Density, Fluids[Particles[i].FluidIndex].RestDensity * 0.01f)
            : Fluids[Particles[i].FluidIndex].RestDensity;
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

            const FVector Dir = Particles[i].Position - Particles[j].Position;
            const float   Dist = Dir.Size();

            if (Dist <= 0.f || Dist > hEff) continue;

            const FVector UnitDir = Dir / Dist;
            const float   dW = SpikyKernelDerivative(Dist, hEff);
            const float   mj = Fluids[Fj].Mass;
            const float   dj = Particles[j].Density;
            const float   pj = Particles[j].Pressure;

            // Pression — page 49
            PressureForce -= mj * (pi / (di * di) + pj / (dj * dj))
                * dW * UnitDir;

            // Viscosité — page 77
            const FVector VelDiff = Particles[j].Velocity - Particles[i].Velocity;
            const float   Denom = Dist * Dist + 0.01f * hEff * hEff;
            ViscosityForce += 2.f * (mj / dj) * VelDiff * (-dW * Dist / Denom);
        }

        // Total Velocity page 80
        Particles[i].Force = PressureForce 
            + (Fluids[Fi].Viscosity * ViscosityForce / di)
            + (bUseGravity ? Gravity * GravityScale : FVector::ZeroVector);
    }
}

void AFluideManager::Integrate(float DeltaTime)                        // PDF 80
{
    TArray<FVector> OldForces;
    OldForces.SetNum(Particles.Num());

    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        OldForces[i] = Particles[i].Force;
        Particles[i].Position += Particles[i].Velocity * DeltaTime
            + 0.5f * OldForces[i] * DeltaTime * DeltaTime;
        Particles[i].Position.Y = 0.f;
    }

    HandleBounds();
    ComputeDensity();
    ComputePressure();
    ComputeForces();

    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        FFluidParticle& P = Particles[i];
        P.Velocity += 0.5f * (OldForces[i] + P.Force) * DeltaTime;
        if (MaxVelocity > 0.f)
        {
            P.Velocity = P.Velocity.GetClampedToMaxSize(MaxVelocity);
        }
        P.Velocity.Y = 0.f;
    }

    HandleBounds();
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
        const FVector InstanceScale = FluidInstanceScales.IsValidIndex(f) ? FluidInstanceScales[f] : ParticleScale;
        T.SetScale3D(InstanceScale);

        const bool bDirty = (ii == FluidISMs[f]->GetInstanceCount() - 1);
        FluidISMs[f]->UpdateInstanceTransform(ii, T, false, bDirty);
    }
}


