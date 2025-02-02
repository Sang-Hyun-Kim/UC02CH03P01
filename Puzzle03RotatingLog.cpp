// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle03RotatingLog.h"

APuzzle03RotatingLog::APuzzle03RotatingLog()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	Root = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LogRoot"));
	Root->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Shapes/Shape_Sphere"));
	if (MeshAsset.Succeeded())
	{
		Root->SetStaticMesh(MeshAsset.Object);
	}
	Root->SetRelativeLocation(FVector(0.0f, 0.0f, -60.0f));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Props/Materials/M_Frame.M_Frame"));
	if (MaterialAsset.Succeeded())
	{
		Root->SetMaterial(0, MaterialAsset.Object);
	}

	float NewRotationSpeed = FMath::RandRange(20.0f, 90.0f);
	RotationSpeed = NewRotationSpeed;
}

void APuzzle03RotatingLog::BeginPlay()
{
	Super::BeginPlay();

}

void APuzzle03RotatingLog::Tick(float DeltatTime)
{
	Super::Tick(DeltatTime);
	RotatingRoot(DeltatTime);
}

void APuzzle03RotatingLog::RotatingRoot(float DeltaTime)
{
	FQuat QuatRotation = FQuat(FRotator(0.0f, RotationSpeed * DeltaTime,0.0f ));
	AddActorLocalRotation(QuatRotation);
}
