// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle04MovingAndPushingObstacle.h"
#include "TimerManager.h"


APuzzle04MovingAndPushingObstacle::APuzzle04MovingAndPushingObstacle()
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

	float NewMovementSpeed = FMath::RandRange(100.0f, 400.0f);
	MovementSpeed = NewMovementSpeed;
	PrimaryActorTick.bCanEverTick = false; // Tick 비활성화
}

void APuzzle04MovingAndPushingObstacle::BeginPlay()
{
	Super::BeginPlay();

	float NewMovementSpeed = FMath::RandRange(20.0f, 200.0f);
	MovementSpeed = NewMovementSpeed;

	StartLocation = GetActorLocation(); // 시작 위치 저장
	// 타이머 설정 (MoveInterval 간격으로 MovePlatform 호출)
	GetWorld()->GetTimerManager().SetTimer(MoveTimerHandle, this, &APuzzle04MovingAndPushingObstacle::Moving, MoveInterval, true);

}

void APuzzle04MovingAndPushingObstacle::Moving()
{
	FVector CurrentLocation = GetActorLocation();

	// 목표 위치 도달 시 방향 반전
	if (FVector::Dist(StartLocation, CurrentLocation) >= TravelDistance)
	{
		MoveDirection *= -1.0f;
	}

	// 이동 처리
	FVector MoveOffset = MoveDirection * MovementSpeed * MoveInterval;
	SetActorLocation(CurrentLocation + MoveOffset);
}

