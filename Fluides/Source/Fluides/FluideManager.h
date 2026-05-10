#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "FluideManager.generated.h"


USTRUCT(BlueprintType)
struct FFluidParticle
{
	GENERATED_BODY()
	FVector Position = FVector::ZeroVector;
	FVector Velocity = FVector::ZeroVector;
	// Acceleration courante calculee par les forces SPH.
	FVector Force = FVector::ZeroVector;
	float   Density = 0.f;
	float   Pressure = 0.f;
	int32   FluidIndex = 0;
};

USTRUCT(BlueprintType)
struct FFluid
{
	GENERATED_BODY()

	// Rendu
	UPROPERTY(EditAnywhere, Category = "Visuel")
	UMaterialInterface* Material = nullptr;

	// Parametres physiques en unites SI
	UPROPERTY(EditAnywhere, Category = "Physique")
	int32 NumParticles = 500;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ToolTip = "Densite au repos en kg/m3. Eau=1000, Huile=870"))
	float RestDensity = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ToolTip = "Constante de Tait. Commence à 50"))
	float TaitK = 1.f;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ToolTip = "Viscosite µ. Eau=0.001, Huile=0.1"))
	float Viscosity = 100.f;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ClampMin = "0.001", ToolTip = "Rayon d'influence h en metres"))
	float InfluenceRadius = 0.3f;

	UPROPERTY(EditAnywhere, Category = "Spawn",
		meta = (ToolTip = "Décalage du centre de spawn en mètres"))
	FVector SpawnOffset = FVector::ZeroVector;

	// Calcule au demarrage a partir de la densite et de la zone de spawn
	float Mass = 0.f;
};


// Constantes de noyau precalculees pour eviter de refaire les memes puissances a chaque voisin.
struct FFluidKernelPair
{
	float H = 0.f;
	float H2 = 0.f;
	float Poly6Coeff = 0.f;
	float SpikyDerivativeCoeff = 0.f;
};

UCLASS()
class FLUIDES_API AFluideManager : public AActor
{
	GENERATED_BODY()

public:
	AFluideManager();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;


	// Rendu
	UPROPERTY(EditAnywhere, Category = "Visuel")
	UStaticMesh* ParticleStaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visuel",
		meta = (ToolTip = "Taille du mesh en metres"))
	FVector ParticleScale = FVector(0.1f, 0.1f, 0.1f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fluids")
	TArray<FFluid> Fluids;

	// Domaine de simulation
	UPROPERTY(EditAnywhere, Category = "Bounds",
		meta = (ToolTip = "Coin bas-gauche en mètres"))
	FVector BoundsMin = FVector(-2.f, -1.f, -2.f);

	UPROPERTY(EditAnywhere, Category = "Bounds",
		meta = (ToolTip = "Coin haut-droite en mètres"))
	FVector BoundsMax = FVector(2.f, 1.f, 2.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	bool bDebugDrawBounds = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Physique",
		meta = (ToolTip = "Active une simulation volumique. Si desactive, la simulation reste en 2D sur le plan X/Z."))
	bool bSimulation3D = false;

	// Forces et collisions
	UPROPERTY(EditAnywhere, Category = "Physique")
	bool bUseGravity = true;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ClampMin = "0.0", ToolTip = "Multiplicateur applique a la gravite"))
	float GravityScale = 1.f;

	UPROPERTY(EditAnywhere, Category = "Physique")
	FVector Gravity = FVector(0.f, 0.f, -9.81f);

	UPROPERTY(EditAnywhere, Category = "Physique")
	float BoundsDamping = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Physique|Bounds",
		meta = (ClampMin = "0.0", ToolTip = "Petite marge en metres qui repousse les particules vers l'interieur quand elles touchent les bounds."))
	float BoundsPushDistance = 0.02f;

	UPROPERTY(EditAnywhere, Category = "Physique|Bounds",
		meta = (ClampMin = "0.0", ToolTip = "Vitesse minimale appliquee vers l'interieur lors d'une collision avec une paroi."))
	float BoundsPushVelocity = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Physique|Integration",
		meta = (ClampMin = "0.0005", ClampMax = "0.02", ToolTip = "Pas maximal de simulation en secondes"))
	float MaxSimulationStep = 0.002f;

	UPROPERTY(EditAnywhere, Category = "Physique|Integration",
		meta = (ClampMin = "1", ClampMax = "32", ToolTip = "Nombre maximal de sous-pas par frame"))
	int32 MaxSimulationSubsteps = 8;

	UPROPERTY(EditAnywhere, Category = "Physique|Integration",
		meta = (ClampMin = "0.0", ToolTip = "Vitesse maximale en m/s. 0 desactive la limite"))
	float MaxVelocity = 1.5f;

	UPROPERTY(EditAnywhere, Category = "Debug")
	bool bDebugFluidValues = false;

	UPROPERTY(EditAnywhere, Category = "Debug",
		meta = (ClampMin = "1"))
	int32 DebugFrameInterval = 30;

	UPROPERTY(EditAnywhere, Category = "Debug|Performance")
	bool bDebugPerformanceValues = false;

	UPROPERTY(EditAnywhere, Category = "Debug|Performance",
		meta = (ClampMin = "1"))
	int32 DebugPerformanceFrameInterval = 60;

private:

	UPROPERTY()
	TArray<UInstancedStaticMeshComponent*> FluidISMs;
	TArray<TArray<FTransform>> FluidTransforms;
	TArray<FFluidParticle> Particles;
	TArray<FFluidKernelPair> KernelPairs;
	// Grille de voisinage: chaque cellule contient les indices des particules proches.
	TArray<TArray<int32>> SpatialGrid;
	float SpatialHashCellSize = 0.3f;
	int32 SpatialGridCountX = 1;
	int32 SpatialGridCountY = 1;
	int32 SpatialGridCountZ = 1;

	int32 DebugFrameCounter = 0;
	int32 DebugPerformanceFrameCounter = 0;
	float PerfHashMs = 0.f;
	float PerfDensityMs = 0.f;
	float PerfPressureMs = 0.f;
	float PerfForcesMs = 0.f;
	float PerfIntegrateMs = 0.f;
	float PerfRenderMs = 0.f;

	// Noyaux SPH et voisinage
	FORCEINLINE float   Poly6Kernel(float r, const FFluidKernelPair& Kernel) const;
	FORCEINLINE float   Poly6KernelFromSquaredDistance(float r2, const FFluidKernelPair& Kernel) const;
	FORCEINLINE float   SpikyKernelDerivative(float r, const FFluidKernelPair& Kernel) const;

	void BuildKernelPairs();
	const FFluidKernelPair& GetKernelPair(int32 FluidA, int32 FluidB) const;
	void BuildSpatialHash();
	FIntVector GetParticleCell(const FVector& Position) const;
	int32 GetCellIndex(const FIntVector& Cell) const;
	bool IsCellValid(const FIntVector& Cell) const;

	// Pipeline de simulation
	void InitFluid(int32 FluidIdx);
	void ComputeDensity();
	void ComputePressure();
	void ComputeForces();
	void Integrate(float DeltaTime);
	void HandleBounds();
	void UpdateInstances();

};
