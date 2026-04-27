// Fill out your copyright notice in the Description page of Project Settings.


#include "FluideManager.h"

// Sets default values
AFluideManager::AFluideManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ParticleMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ParticleMesh"));
	SetRootComponent(ParticleMesh);

	ParticleMesh->SetMobility(EComponentMobility::Movable);
	ParticleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ParticleMesh->SetGenerateOverlapEvents(false);
	ParticleMesh->bReceivesDecals = false;
	ParticleMesh->CastShadow = false;
}

// Called when the game starts or when spawned
void AFluideManager::BeginPlay()
{
	Super::BeginPlay();

	if (ParticleStaticMesh)
	{
		ParticleMesh->SetStaticMesh(ParticleStaticMesh);
	}
	if (bDebugDrawBounds)
	{
		const FVector Center = (BoundsMin + BoundsMax) * 0.5f;
		const FVector Extents = (BoundsMax - BoundsMin) * 0.5f;
		DrawDebugBox(GetWorld(), Center, Extents, FColor::Cyan, false, 0.f, 0, 2.f);
	}
	for (FFluid Fluid : Fluids)
	{
		InitFluid(Fluid);
	}

	
}

// Called every frame
void AFluideManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFluideManager::InitFluid(FFluid& Fluid)
{
    // 1. Calcul de la masse (en kg) 
    // Note: Utilise ContentVolum que tu as ajouté dans la classe
    float ParticleMass = (ContentVolum * Fluid.RestDensity) / Fluid.NumParticles;
    Fluid.Mass = ParticleMass; // On met à jour la struct pour info

    // 2. Vider les instances précédentes au cas où
    ParticleMesh->ClearInstances();
    Particles.Empty();

    // 3. Création des particules
    for (int32 i = 0; i < Fluid.NumParticles; ++i)
    {
        FFluidParticle NewParticle;

        // Positionnement initial (ici en cube/grille pour l'exemple)
        // Unreal utilise les cm, donc on espace un peu
        float Spacing = 20.0f;
        int32 GridSize = FMath::CeilToInt(FMath::Pow(Fluid.NumParticles, 1.f / 3.f));

        FVector Pos = FVector(
            (i % GridSize) * Spacing,
            ((i / GridSize) % GridSize) * Spacing,
            (i / (GridSize * GridSize)) * Spacing
        );

        NewParticle.Position = Pos;
        NewParticle.Velocity = FVector::ZeroVector;
        NewParticle.Force = FVector::ZeroVector;
        NewParticle.Density = Fluid.RestDensity; // Initialisée au repos 
        NewParticle.Pressure = 0.0f;

        Particles.Add(NewParticle);

        // 4. Ajouter l'instance visuelle dans Unreal
        FTransform InstanceTransform;
        InstanceTransform.SetLocation(Pos);

        ParticleMesh->AddInstance(InstanceTransform);
    }
}

