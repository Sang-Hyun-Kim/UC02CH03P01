// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle01RotatingPlaform.h"

APuzzle01RotatingPlaform::APuzzle01RotatingPlaform()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Shapes/Shape_Cube.Shape_Cube"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	StaticMeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, -60.0f));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Props/Materials/M_Frame.M_Frame"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	float NewRotationSpeed = FMath::RandRange(20.0f, 90.0f);
	RotationSpeed = NewRotationSpeed;

	//float NewScale = FMath::RandRange(0.5f, 2.0f);
	//PRScale = FVector(NewScale, NewScale, NewScale);
	//StaticMeshComp->SetRelativeScale3D(PRScale);
}

void APuzzle01RotatingPlaform::BeginPlay()
{
	Super::BeginPlay();
}

void APuzzle01RotatingPlaform::Tick(float DeltatTime)
{
	Super::Tick(DeltatTime);

	Rotating(DeltatTime);
}

void APuzzle01RotatingPlaform::Rotating(float DeltaTime)
{
	FQuat QuatRotation = FQuat(FRotator(RotationSpeed * DeltaTime, 0.0f, 0.0f));
	AddActorLocalRotation(QuatRotation);
}
