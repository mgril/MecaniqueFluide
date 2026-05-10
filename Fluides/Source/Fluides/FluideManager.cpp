#include "FluideManager.h"
#include "Async/ParallelFor.h"

AFluideManager::AFluideManager()
{
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}


void AFluideManager::BeginPlay()
{
	Super::BeginPlay();

    if (bSimulation3D && BoundsMax.Y <= BoundsMin.Y + KINDA_SMALL_NUMBER)
    {
        BoundsMin.Y = -1.f;
        BoundsMax.Y = 1.f;
    }

    if (bDebugDrawBounds)
    {
        const FVector Center = (BoundsMin + BoundsMax) * 0.5f * 100.f;
        const FVector Extents = (BoundsMax - BoundsMin) * 0.5f * 100.f;
        DrawDebugBox(GetWorld(), Center, Extents, FColor::Cyan, true, -1.f, 0, 2.f);
    }

    // Un InstancedStaticMesh par fluide permet de garder un materiau different pour chaque type.
    FluidISMs.SetNum(Fluids.Num());
    FluidTransforms.SetNum(Fluids.Num());
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

        if (ParticleStaticMesh) ISM->SetStaticMesh(ParticleStaticMesh);
        if (Fluids[f].Material) ISM->SetMaterial(0, Fluids[f].Material);

        FluidISMs[f] = ISM;
        InitFluid(f);
    }

    BuildKernelPairs();
    ComputeDensity();
    ComputePressure();
    ComputeForces();
    UpdateInstances();
}

void AFluideManager::InitFluid(int32 FluidIdx)
{
    FFluid& Fluid = Fluids[FluidIdx];
    // Chaque fluide recoit une zone de spawn separee quand plusieurs fluides sont presents.
    // Cela evite que deux fluides demarrent exactement au meme endroit.
    const FVector BoxSize = BoundsMax - BoundsMin;
    const int32 FluidCount = FMath::Max(Fluids.Num(), 1);

    FVector SpawnMin = BoundsMin;
    FVector SpawnMax = BoundsMax;

    if (FluidCount > 1)
    {
        const float LaneWidth = BoxSize.X / FluidCount;
        SpawnMin.X = BoundsMin.X + LaneWidth * FluidIdx;
        SpawnMax.X = SpawnMin.X + LaneWidth;
    }
    // L'offset reste un reglage manuel pratique pour tester differentes positions de depart.
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
    if (SpawnMin.Y < BoundsMin.Y)
    {
        const float Shift = BoundsMin.Y - SpawnMin.Y;
        SpawnMin.Y += Shift;
        SpawnMax.Y += Shift;
    }
    if (SpawnMax.Y > BoundsMax.Y)
    {
        const float Shift = SpawnMax.Y - BoundsMax.Y;
        SpawnMin.Y -= Shift;
        SpawnMax.Y -= Shift;
    }

    const FVector SpawnBoxSize = SpawnMax - SpawnMin;

    Fluid.InfluenceRadius = FMath::Max(Fluid.InfluenceRadius, KINDA_SMALL_NUMBER);
    // Masse automatique: densite cible * aire en 2D, ou volume en 3D.
    // Comme ca, changer le nombre de particules ne change pas toute la quantite de fluide.
    const float Measure = bSimulation3D
        ? SpawnBoxSize.X * SpawnBoxSize.Y * SpawnBoxSize.Z
        : SpawnBoxSize.X * SpawnBoxSize.Z;
    Fluid.Mass = (Fluid.NumParticles > 0)
        ? (Fluid.RestDensity * FMath::Max(Measure, KINDA_SMALL_NUMBER)) / Fluid.NumParticles
        : 1.f;
    if (bSimulation3D)
    {
        // En 3D, on remplit un volume au lieu d'une grille plate X/Z.
        const float Volume = FMath::Max(SpawnBoxSize.X * SpawnBoxSize.Y * SpawnBoxSize.Z, KINDA_SMALL_NUMBER);
        const float ParticlesPerMeter = FMath::Pow((float)Fluid.NumParticles / Volume, 1.f / 3.f);
        const int32 CountX = FMath::Max(1, FMath::CeilToInt(SpawnBoxSize.X * ParticlesPerMeter));
        const int32 CountY = FMath::Max(1, FMath::CeilToInt(SpawnBoxSize.Y * ParticlesPerMeter));
        const int32 CountZ = FMath::Max(1, FMath::CeilToInt((float)Fluid.NumParticles / FMath::Max(1, CountX * CountY)));
        const float Step3DX = SpawnBoxSize.X / CountX;
        const float Step3DY = SpawnBoxSize.Y / CountY;
        const float Step3DZ = SpawnBoxSize.Z / CountZ;

        int32 Spawned3D = 0;
        for (int32 z = 0; z < CountZ && Spawned3D < Fluid.NumParticles; ++z)
        {
            for (int32 y = 0; y < CountY && Spawned3D < Fluid.NumParticles; ++y)
            {
                for (int32 x = 0; x < CountX && Spawned3D < Fluid.NumParticles; ++x)
                {
                    FVector Pos = FVector(
                        SpawnMin.X + Step3DX * (x + 0.5f),
                        SpawnMin.Y + Step3DY * (y + 0.5f),
                        SpawnMin.Z + Step3DZ * (z + 0.5f)
                    );
                    Pos.X = FMath::Clamp(Pos.X, BoundsMin.X, BoundsMax.X);
                    Pos.Y = FMath::Clamp(Pos.Y, BoundsMin.Y, BoundsMax.Y);
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
                    T.SetLocation(Pos * 100.f);
                    T.SetScale3D(ParticleScale);
                    FluidISMs[FluidIdx]->AddInstance(T);
                    ++Spawned3D;
                }
            }
        }

        return;
    }

    // Grille de spawn 2D adaptee au ratio de la zone.
    const float AspectRatio = FMath::Max(SpawnBoxSize.X / FMath::Max(SpawnBoxSize.Z, KINDA_SMALL_NUMBER), KINDA_SMALL_NUMBER);
    const int32 Cols = FMath::Max(1, FMath::CeilToInt(FMath::Sqrt((float)Fluid.NumParticles * AspectRatio)));
    const int32 Rows = FMath::Max(1, FMath::CeilToInt((float)Fluid.NumParticles / Cols));
    const float StepX = SpawnBoxSize.X / Cols;
    const float StepZ = SpawnBoxSize.Z / Rows;

    int32 Spawned = 0;
    for (int32 row = 0; row < Rows && Spawned < Fluid.NumParticles; ++row)
    {
        const int32 Remaining = Fluid.NumParticles - Spawned;
        const int32 RowsLeft = Rows - row;
        const int32 CountThisRow = FMath::Min(Cols, FMath::CeilToInt((float)Remaining / RowsLeft));
        const float RowWidth = (CountThisRow - 1) * StepX;
        const float StartX = (SpawnMin.X + SpawnMax.X) * 0.5f - RowWidth * 0.5f;
        // Une ligne sur deux est decalee pour eviter un bloc trop parfaitement aligne.
        const float Stagger = (CountThisRow > 1 && (row % 2) == 1) ? StepX * 0.5f : 0.f;

        for (int32 col = 0; col < CountThisRow && Spawned < Fluid.NumParticles; ++col)
        {
            FVector Pos = FVector(
                StartX + col * StepX + Stagger,
                0.f,
                SpawnMin.Z + StepZ * (row + 0.5f)
            );

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
            T.SetLocation(Pos * 100.f);
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

    PerfHashMs = 0.f;
    PerfDensityMs = 0.f;
    PerfPressureMs = 0.f;
    PerfForcesMs = 0.f;
    PerfIntegrateMs = 0.f;
    PerfRenderMs = 0.f;

    const double IntegrateStart = FPlatformTime::Seconds();
    // On decoupe la frame en sous-pas pour garder la simulation stable quand le framerate varie.
    const float SimDeltaTime = FMath::Min(DeltaTime, MaxSimulationStep * MaxSimulationSubsteps);
    const int32 StepCount = FMath::Max(1, FMath::CeilToInt(SimDeltaTime / MaxSimulationStep));
    const float StepDeltaTime = SimDeltaTime / StepCount;

    for (int32 Step = 0; Step < StepCount; ++Step)
    {
        Integrate(StepDeltaTime);
    }

    PerfIntegrateMs = static_cast<float>((FPlatformTime::Seconds() - IntegrateStart) * 1000.0);

    const double RenderStart = FPlatformTime::Seconds();
    UpdateInstances();
    PerfRenderMs = static_cast<float>((FPlatformTime::Seconds() - RenderStart) * 1000.0);

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
    if (bDebugPerformanceValues && ++DebugPerformanceFrameCounter >= DebugPerformanceFrameInterval)
    {
        DebugPerformanceFrameCounter = 0;
        UE_LOG(LogTemp, Log, TEXT("Fluid perf | hash %.3f ms | density %.3f ms | pressure %.3f ms | forces %.3f ms | integrate %.3f ms | render %.3f ms"),
            PerfHashMs, PerfDensityMs, PerfPressureMs, PerfForcesMs, PerfIntegrateMs, PerfRenderMs);
    }
}

void AFluideManager::BuildKernelPairs()
{
    // Precalcule les constantes des noyaux pour chaque couple de fluides.
    const int32 FluidCount = Fluids.Num();
    KernelPairs.SetNum(FluidCount * FluidCount);

    for (int32 a = 0; a < FluidCount; ++a)
    {
        for (int32 b = 0; b < FluidCount; ++b)
        {
            FFluidKernelPair& Kernel = KernelPairs[a * FluidCount + b];
            Kernel.H = FMath::Max((Fluids[a].InfluenceRadius + Fluids[b].InfluenceRadius) * 0.5f, KINDA_SMALL_NUMBER);
            Kernel.H2 = Kernel.H * Kernel.H;

            const float h3 = Kernel.H2 * Kernel.H;
            const float h6 = h3 * h3;
            const float h9 = h6 * h3;
            Kernel.Poly6Coeff = 315.f / (64.f * PI * h9);
            Kernel.SpikyDerivativeCoeff = -45.f / (PI * h6);
        }
    }
}

const FFluidKernelPair& AFluideManager::GetKernelPair(int32 FluidA, int32 FluidB) const
{
    return KernelPairs[FluidA * Fluids.Num() + FluidB];
}

void AFluideManager::BuildSpatialHash()
{
    float MaxRadius = KINDA_SMALL_NUMBER;
    for (const FFluid& Fluid : Fluids)
    {
        MaxRadius = FMath::Max(MaxRadius, Fluid.InfluenceRadius);
    }

    // Le hash spatial evite de comparer chaque particule avec toutes les autres.
    SpatialHashCellSize = MaxRadius;
    const float SafeCellSize = FMath::Max(SpatialHashCellSize, KINDA_SMALL_NUMBER);
    const FVector BoundsSize = BoundsMax - BoundsMin;
    SpatialGridCountX = FMath::Max(1, FMath::CeilToInt(BoundsSize.X / SafeCellSize));
    SpatialGridCountY = bSimulation3D ? FMath::Max(1, FMath::CeilToInt(BoundsSize.Y / SafeCellSize)) : 1;
    SpatialGridCountZ = FMath::Max(1, FMath::CeilToInt(BoundsSize.Z / SafeCellSize));

    const int32 CellCount = SpatialGridCountX * SpatialGridCountY * SpatialGridCountZ;
    if (SpatialGrid.Num() != CellCount)
    {
        SpatialGrid.SetNum(CellCount);
    }

    for (TArray<int32>& CellParticles : SpatialGrid)
    {
        CellParticles.Reset();
    }

    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        const FIntVector Cell = GetParticleCell(Particles[i].Position);
        SpatialGrid[GetCellIndex(Cell)].Add(i);
    }
}

FIntVector AFluideManager::GetParticleCell(const FVector& Position) const
{
    const float SafeCellSize = FMath::Max(SpatialHashCellSize, KINDA_SMALL_NUMBER);
    return FIntVector(
        FMath::Clamp(FMath::FloorToInt((Position.X - BoundsMin.X) / SafeCellSize), 0, SpatialGridCountX - 1),
        bSimulation3D ? FMath::Clamp(FMath::FloorToInt((Position.Y - BoundsMin.Y) / SafeCellSize), 0, SpatialGridCountY - 1) : 0,
        FMath::Clamp(FMath::FloorToInt((Position.Z - BoundsMin.Z) / SafeCellSize), 0, SpatialGridCountZ - 1)
    );
}

int32 AFluideManager::GetCellIndex(const FIntVector& Cell) const
{
    return (Cell.Z * SpatialGridCountY + Cell.Y) * SpatialGridCountX + Cell.X;
}

bool AFluideManager::IsCellValid(const FIntVector& Cell) const
{
    return Cell.X >= 0 && Cell.X < SpatialGridCountX
        && Cell.Y >= 0 && Cell.Y < SpatialGridCountY
        && Cell.Z >= 0 && Cell.Z < SpatialGridCountZ;
}
// Noyaux SPH

float AFluideManager::Poly6Kernel(float r, const FFluidKernelPair& Kernel) const
{
    if (r > Kernel.H) return 0.f;

    const float V = Kernel.H2 - (r * r);
    return Kernel.Poly6Coeff * V * V * V;
}

float AFluideManager::Poly6KernelFromSquaredDistance(float r2, const FFluidKernelPair& Kernel) const
{
    // Version sans racine car Poly6 depend directement de r^2.
    if (r2 > Kernel.H2) return 0.f;

    const float V = Kernel.H2 - r2;
    return Kernel.Poly6Coeff * V * V * V;
}


float AFluideManager::SpikyKernelDerivative(float r, const FFluidKernelPair& Kernel) const
{
    if (r > Kernel.H || r <= 0.f) return 0.f;

    const float V = Kernel.H - r;
    return Kernel.SpikyDerivativeCoeff * V * V;
}

void AFluideManager::ComputeDensity()
{
    const double HashStart = FPlatformTime::Seconds();
    BuildSpatialHash();
    PerfHashMs += static_cast<float>((FPlatformTime::Seconds() - HashStart) * 1000.0);

    const double DensityStart = FPlatformTime::Seconds();
    const bool bForceSingleThread = Particles.Num() < 256;
    ParallelFor(Particles.Num(), [this](int32 i)
    {
        float Density = 0.f;
        const FIntVector Cell = GetParticleCell(Particles[i].Position);
        // En 2D, Y reste fixe: on parcourt donc 9 cellules au lieu de 27.
        const int32 MinOffsetY = bSimulation3D ? -1 : 0;
        const int32 MaxOffsetY = bSimulation3D ? 1 : 0;

        for (int32 OffsetX = -1; OffsetX <= 1; ++OffsetX)
        {
            for (int32 OffsetY = MinOffsetY; OffsetY <= MaxOffsetY; ++OffsetY)
            {
                for (int32 OffsetZ = -1; OffsetZ <= 1; ++OffsetZ)
                {
                    const FIntVector NeighborCell(Cell.X + OffsetX, Cell.Y + OffsetY, Cell.Z + OffsetZ);
                    if (!IsCellValid(NeighborCell)) continue;

                    const TArray<int32>& Bucket = SpatialGrid[GetCellIndex(NeighborCell)];
                    for (const int32 j : Bucket)
                    {
                        if (i == j) continue;

                        const FFluidKernelPair& Kernel = GetKernelPair(Particles[i].FluidIndex, Particles[j].FluidIndex);
                        const FVector Delta = Particles[i].Position - Particles[j].Position;
                        const float DistSq = Delta.SizeSquared();

                        if (DistSq > Kernel.H2) continue;

                        Density += Fluids[Particles[j].FluidIndex].Mass
                            * Poly6KernelFromSquaredDistance(DistSq, Kernel);
                    }
                }
            }
        }

        // Si une particule n'a aucun voisin, on garde au minimum sa densite de repos.
        Particles[i].Density = (Density > 0.f)
            ? FMath::Max(Density, Fluids[Particles[i].FluidIndex].RestDensity * 0.01f)
            : Fluids[Particles[i].FluidIndex].RestDensity;
    }, bForceSingleThread);

    PerfDensityMs += static_cast<float>((FPlatformTime::Seconds() - DensityStart) * 1000.0);
}

void AFluideManager::ComputePressure()
{
    const double PressureStart = FPlatformTime::Seconds();
    const bool bForceSingleThread = Particles.Num() < 256;
    ParallelFor(Particles.Num(), [this](int32 i)
    {
        FFluidParticle& P = Particles[i];
        const FFluid& F = Fluids[P.FluidIndex];
        const float Ratio = P.Density / F.RestDensity;
        // Pas de pression negative pour eviter une attraction artificielle.
        P.Pressure = FMath::Max(0.f, F.TaitK * (FMath::Pow(Ratio, 7.f) - 1.f));
    }, bForceSingleThread);

    PerfPressureMs += static_cast<float>((FPlatformTime::Seconds() - PressureStart) * 1000.0);
}

void AFluideManager::ComputeForces()
{
    const double ForcesStart = FPlatformTime::Seconds();
    const bool bForceSingleThread = Particles.Num() < 256;
    ParallelFor(Particles.Num(), [this](int32 i)
    {
        const int32 Fi = Particles[i].FluidIndex;
        const float di = Particles[i].Density;
        const float pi = Particles[i].Pressure;
        const FIntVector Cell = GetParticleCell(Particles[i].Position);
        // En 2D, Y reste fixe: on parcourt donc 9 cellules au lieu de 27.
        const int32 MinOffsetY = bSimulation3D ? -1 : 0;
        const int32 MaxOffsetY = bSimulation3D ? 1 : 0;

        FVector PressureForce = FVector::ZeroVector;
        FVector ViscosityForce = FVector::ZeroVector;
        // La pression repousse les particules trop proches, la viscosite lisse les vitesses.

        for (int32 OffsetX = -1; OffsetX <= 1; ++OffsetX)
        {
            for (int32 OffsetY = MinOffsetY; OffsetY <= MaxOffsetY; ++OffsetY)
            {
                for (int32 OffsetZ = -1; OffsetZ <= 1; ++OffsetZ)
                {
                    const FIntVector NeighborCell(Cell.X + OffsetX, Cell.Y + OffsetY, Cell.Z + OffsetZ);
                    if (!IsCellValid(NeighborCell)) continue;

                    const TArray<int32>& Bucket = SpatialGrid[GetCellIndex(NeighborCell)];
                    for (const int32 j : Bucket)
                    {
                        if (i == j) continue;

                        const int32 Fj = Particles[j].FluidIndex;
                        const FFluidKernelPair& Kernel = GetKernelPair(Fi, Fj);

                        const FVector Dir = Particles[i].Position - Particles[j].Position;
                        const float DistSq = Dir.SizeSquared();

                        if (DistSq <= KINDA_SMALL_NUMBER || DistSq > Kernel.H2) continue;

                        const float Dist = FMath::Sqrt(DistSq);
                        const FVector UnitDir = Dir / Dist;
                        const float dW = SpikyKernelDerivative(Dist, Kernel);
                        const float mj = Fluids[Fj].Mass;
                        const float dj = Particles[j].Density;
                        const float pj = Particles[j].Pressure;

                        PressureForce -= mj * (pi / (di * di) + pj / (dj * dj))
                            * dW * UnitDir;

                        const FVector VelDiff = Particles[j].Velocity - Particles[i].Velocity;
                        const float Denom = Dist * Dist + 0.01f * Kernel.H2;
                        ViscosityForce += 2.f * (mj / dj) * VelDiff * (-dW * Dist / Denom);
                    }
                }
            }
        }
        // Force est utilisee comme acceleration: pression + viscosite + gravite.
        Particles[i].Force = PressureForce
            + (Fluids[Fi].Viscosity * ViscosityForce / di)
            + (bUseGravity ? Gravity * GravityScale : FVector::ZeroVector);
    }, bForceSingleThread);

    PerfForcesMs += static_cast<float>((FPlatformTime::Seconds() - ForcesStart) * 1000.0);
}

void AFluideManager::Integrate(float DeltaTime)
{
    TArray<FVector> OldForces;
    OldForces.SetNum(Particles.Num());
    // Integration de Verlet: position avec l'ancienne acceleration, puis vitesse avec ancienne+nouvelles forces.

    const bool bForceSingleThread = Particles.Num() < 256;
    ParallelFor(Particles.Num(), [this, &OldForces, DeltaTime](int32 i)
    {
        OldForces[i] = Particles[i].Force;
        Particles[i].Position += Particles[i].Velocity * DeltaTime
            + 0.5f * OldForces[i] * DeltaTime * DeltaTime;
        if (!bSimulation3D)
        {
            Particles[i].Position.Y = 0.f;
        }
    }, bForceSingleThread);

    HandleBounds();

    // Les forces dependent des nouvelles positions, donc on recalcule densite, pression et forces avant la vitesse.
    ComputeDensity();
    ComputePressure();
    ComputeForces();

    ParallelFor(Particles.Num(), [this, &OldForces, DeltaTime](int32 i)
    {
        FFluidParticle& P = Particles[i];
        P.Velocity += 0.5f * (OldForces[i] + P.Force) * DeltaTime;
        if (MaxVelocity > 0.f)
        {
            P.Velocity = P.Velocity.GetClampedToMaxSize(MaxVelocity);
        }
        if (!bSimulation3D)
        {
            P.Velocity.Y = 0.f;
        }
    }, bForceSingleThread);

    HandleBounds();
}

void AFluideManager::HandleBounds()
{
    // Les bounds ne font pas qu'arreter la particule: ils la repoussent legerement vers l'interieur.
    const float PushDistance = FMath::Max(BoundsPushDistance, 0.f);
    const float PushVelocity = FMath::Max(BoundsPushVelocity, 0.f);

    for (FFluidParticle& P : Particles)
    {
        const float MinX = BoundsMin.X + PushDistance;
        const float MaxX = BoundsMax.X - PushDistance;
        const float MinY = BoundsMin.Y + PushDistance;
        const float MaxY = BoundsMax.Y - PushDistance;
        const float MinZ = BoundsMin.Z + PushDistance;
        const float MaxZ = BoundsMax.Z - PushDistance;

        // Paroi gauche
        if (P.Position.X < MinX)
        {
            P.Position.X = MinX;
            P.Velocity.X = FMath::Max(FMath::Abs(P.Velocity.X) * BoundsDamping, PushVelocity);
            P.Velocity.Y *= BoundsDamping;
            P.Velocity.Z *= BoundsDamping;
        }
        // Paroi droite
        if (P.Position.X > MaxX)
        {
            P.Position.X = MaxX;
            P.Velocity.X = -FMath::Max(FMath::Abs(P.Velocity.X) * BoundsDamping, PushVelocity);
            P.Velocity.Y *= BoundsDamping;
            P.Velocity.Z *= BoundsDamping;
        }

        if (bSimulation3D)
        {
            // Paroi -Y
            if (P.Position.Y < MinY)
            {
                P.Position.Y = MinY;
                P.Velocity.Y = FMath::Max(FMath::Abs(P.Velocity.Y) * BoundsDamping, PushVelocity);
                P.Velocity.X *= BoundsDamping;
                P.Velocity.Z *= BoundsDamping;
            }
            // Paroi +Y
            if (P.Position.Y > MaxY)
            {
                P.Position.Y = MaxY;
                P.Velocity.Y = -FMath::Max(FMath::Abs(P.Velocity.Y) * BoundsDamping, PushVelocity);
                P.Velocity.X *= BoundsDamping;
                P.Velocity.Z *= BoundsDamping;
            }
        }

        // Sol
        if (P.Position.Z < MinZ)
        {
            P.Position.Z = MinZ;
            P.Velocity.Z = FMath::Max(FMath::Abs(P.Velocity.Z) * BoundsDamping, PushVelocity);
            P.Velocity.X *= BoundsDamping;
            P.Velocity.Y *= BoundsDamping;
        }
        // Haut
        if (P.Position.Z > MaxZ)
        {
            P.Position.Z = MaxZ;
            P.Velocity.Z = -FMath::Max(FMath::Abs(P.Velocity.Z) * BoundsDamping, PushVelocity);
            P.Velocity.X *= BoundsDamping;
            P.Velocity.Y *= BoundsDamping;
        }
    }
}

void AFluideManager::UpdateInstances()
{
    TArray<int32> Counters;
    Counters.SetNumZeroed(Fluids.Num());
    // On prepare les transforms par fluide pour faire une mise a jour batch, plus rapide que instance par instance.

    for (int32 f = 0; f < Fluids.Num(); ++f)
    {
        const int32 InstanceCount = FluidISMs[f] ? FluidISMs[f]->GetInstanceCount() : 0;
        FluidTransforms[f].SetNum(InstanceCount);
    }

    for (int32 i = 0; i < Particles.Num(); ++i)
    {
        const int32 f = Particles[i].FluidIndex;
        const int32 ii = Counters[f]++;

        FTransform T;
        T.SetLocation(Particles[i].Position * 100.f);
        T.SetScale3D(ParticleScale);

        if (FluidTransforms.IsValidIndex(f) && FluidTransforms[f].IsValidIndex(ii))
        {
            FluidTransforms[f][ii] = T;
        }
    }

    for (int32 f = 0; f < FluidISMs.Num(); ++f)
    {
        if (FluidISMs[f] && FluidTransforms.IsValidIndex(f) && FluidTransforms[f].Num() > 0)
        {
            FluidISMs[f]->BatchUpdateInstancesTransforms(0, FluidTransforms[f], false, true, true);
        }
    }
}


