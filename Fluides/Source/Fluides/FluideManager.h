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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	int32 NumParticles = 1000;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	float RestDensity = 1000; // kg/m^3

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	float TaitK = 1000; // parametre de rigidité

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	float ViscosityFactor = 1000; // µ

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	float InfluenceRadius = 1000; // metre

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	float Mass = 1000; // parametre de rigidité
};
USTRUCT(BlueprintType)
struct FFluidParticle
{
	GENERATED_BODY()

	FVector Position;
	FVector Velocity;
	FVector Force;
	float Density;
	float Pressure;
};

UCLASS()
class FLUIDES_API AFluideManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFluideManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// ------------------------
// Render
// ------------------------
	UPROPERTY(VisibleAnywhere, Category = "Particles|Render")
	UInstancedStaticMeshComponent* ParticleMesh;  

	UPROPERTY(EditAnywhere, Category = "Particles|Render")
	UStaticMesh* ParticleStaticMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles")
	TArray<FFluid> Fluids;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particles|Parameters")
	float ContentVolum = 1000; // m^3

	UFUNCTION()
	void InitFluid(FFluid& Fluid);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	bool bDebugDrawBounds = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	FVector BoundsMin = FVector(-3000.f, -3000.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Particles|Bounds")
	FVector BoundsMax = FVector(3000.f, 3000.f, 2000.f);

	TArray<FFluidParticle> Particles;


};
