// Fill out your copyright notice in the Description page of Project Settings.


#include "Puzzle05BlinkPlatform.h"
#include "TimerManager.h"

APuzzle05BlinkPlatform::APuzzle05BlinkPlatform()
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
	PrimaryActorTick.bCanEverTick = false;
}

void APuzzle05BlinkPlatform::BeginPlay()
{
	Super::BeginPlay();
	TogglePlatformState();
	// 타이머 설정: 5초마다 상태를 변경
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &APuzzle05BlinkPlatform::TogglePlatformState, ToggleTimer, true);


}

void APuzzle05BlinkPlatform::TogglePlatformState()
{
	// 상태를 반전시킵니다
	if (bIsActive)
	{
		bIsActive = false;
	}
	else
	{
		bIsActive = true;
	}

	Root->SetVisibility(bIsActive);
	SetActorEnableCollision(bIsActive); // 충돌을 활성화/비활성화
}
