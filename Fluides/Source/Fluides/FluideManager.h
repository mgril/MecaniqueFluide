// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "FluideManager.generated.h"


USTRUCT(BlueprintType)
struct FFluid
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Particles|Visuel") //need creation of dynamic material instance to change material color
	UMaterialInterface* Material = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	int32 NumParticles = 200; // objectif 2000

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters", meta = (ToolTip = "Densité au repos kg/m³ — eau=1000, huile=870"))
	float RestDensity = 1000; // kg/m^3 water = 1000 oil 870

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters", meta = (ToolTip = "Constante de Tait — rigidité du fluide"))
	float TaitK = 200; // fluid rigidity

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters", meta = (ToolTip = "Viscosité µ"))
	float Viscosity = 2; // µ

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters", meta = (ToolTip = "Rayon d'influence h en mètres"))
	float InfluenceRadius = 15; // cm

	// Interactions cross-fluide 
	// > 1 = repulsion (immiscibilité huile/eau)
	// < 1 = attraction entre fluides
	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (ToolTip = "Facteur de pression cross-fluide. 1=neutre, >1=immiscible"))
	float CrossPressureFactor = 1.f;

	// > 1 = freinage mutuel fort
	// < 1 = les fluides glissent l'un sur l'autre
	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (ToolTip = "Facteur de viscosité cross-fluide"))
	float CrossViscosityFactor = 1.f;

	//  Runtime
	float Mass = 0.f;  // calculé au démarrage
};
USTRUCT(BlueprintType)
struct FFluidParticle
{
	GENERATED_BODY()

	FVector Position = FVector::ZeroVector;
	FVector Velocity = FVector::ZeroVector;
	FVector Force = FVector::ZeroVector; // accumulate acceleration 
	float Density = 0.f;
	float Pressure = 0.f;
	int32 FluidIndex = 0; // whose fluid is the owner
};

UCLASS()
class FLUIDES_API AFluideManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFluideManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected: 

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
// Params 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fluids")
	TArray<FFluid> Fluids;

	// Render
	UPROPERTY(EditAnywhere, Category = "Particles|Render")
	UStaticMesh* ParticleStaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particles|Render")
	UInstancedStaticMeshComponent* ParticleMesh; 

	UPROPERTY(EditAnywhere, Category = "Particles|Render",
		meta = (ToolTip = "Taille du mesh de la particule"))
	FVector ParticleScale = FVector(1.f, 1.f, 1.f);

	//Bounds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	FVector BoundsMin = FVector(-200.f, 0.f, -200.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	FVector BoundsMax = FVector(200.f, 0.f, 200.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	bool bDebugDrawBounds = true;

	//Physic
	UPROPERTY(EditAnywhere, Category = "Physic")
	float BoundsDamping = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Physic")
	FVector Gravity = FVector(0.f, 0.f, -981.f); //cm/s2

	UPROPERTY()
	TArray<UInstancedStaticMeshComponent*> FluidISMs;

	TArray<FFluidParticle> Particles;

private:

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

	// Helpers cross-fluide                   need?
	FORCEINLINE float GetCrossPressureFactor(int32 A, int32 B)  const;
	FORCEINLINE float GetCrossViscosityFactor(int32 A, int32 B) const;
};
