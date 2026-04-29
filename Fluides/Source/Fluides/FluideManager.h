// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "FluideManager.generated.h"


USTRUCT(BlueprintType)
struct FFluidParticle
{
	GENERATED_BODY()
	FVector Position = FVector::ZeroVector;  // metres
	FVector Velocity = FVector::ZeroVector;  // metres/seconde
	FVector Force = FVector::ZeroVector;  // acceleration m/s2
	float   Density = 0.f;                  // kg/m3
	float   Pressure = 0.f;                  // Pa
	int32   FluidIndex = 0;
};

USTRUCT(BlueprintType)
struct FFluid
{
	GENERATED_BODY()

	// Visuel
	UPROPERTY(EditAnywhere, Category = "Visuel")
	UMaterialInterface* Material = nullptr;

	// Physique - toutes les valeurs en unites SI (metres, kg) OBJ 2000
	UPROPERTY(EditAnywhere, Category = "Physique")
	int32 NumParticles = 100;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ToolTip = "Densite au repos en kg/m3. Eau=1000, Huile=870"))
	float RestDensity = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ToolTip = "Constante de Tait. Commence à 50"))
	float TaitK = 50.f;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ToolTip = "Viscosite µ. Eau=0.001, Huile=0.1"))
	float Viscosity = 0.001f;

	UPROPERTY(EditAnywhere, Category = "Physique",
		meta = (ToolTip = "Rayon d'influence h en METRES. Commence à 0.1 taille du mesh initial"))
	float InfluenceRadius = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Spawn",
		meta = (ToolTip = "Décalage du centre de spawn en mètres"))
	FVector SpawnOffset = FVector::ZeroVector;

	// Runtime — calcule au démarrage, pas éditable
	float Mass = 0.f;
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


	// ------------ Render -------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Visuel")
	UStaticMesh* ParticleStaticMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Visuel",
		meta = (ToolTip = "Taille du mesh en metres"))
	FVector ParticleScale = FVector(0.1f, 0.1f, 0.1f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fluids")
	TArray<FFluid> Fluids;

	//     Bounds
	UPROPERTY(EditAnywhere, Category = "Bounds",
		meta = (ToolTip = "Coin bas-gauche en mètres"))
	FVector BoundsMin = FVector(-2.f, 0.f, -2.f);

	UPROPERTY(EditAnywhere, Category = "Bounds",
		meta = (ToolTip = "Coin haut-droite en mètres"))
	FVector BoundsMax = FVector(2.f, 0.f, 2.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	bool bDebugDrawBounds = true;

	// Gravité en m/s2
	UPROPERTY(EditAnywhere, Category = "Physique")
	FVector Gravity = FVector(0.f, 0.f, -9.81f);

	UPROPERTY(EditAnywhere, Category = "Physique")
	float BoundsDamping = 0.5f;

private:

	UPROPERTY()
	TArray<UInstancedStaticMeshComponent*> FluidISMs;

	TArray<FFluidParticle> Particles;

	// Kernel functions en m
	FORCEINLINE float   Poly6Kernel(float r, float h);
	FORCEINLINE float   SpikyKernelDerivative(float r, float h);

	//    Pipeline SPH
	void InitFluid(int32 FluidIdx);
	void ComputeDensity();
	void ComputePressure();
	void ComputeForces();
	void Integrate(float DeltaTime);
	void HandleBounds();
	void UpdateInstances();

};
