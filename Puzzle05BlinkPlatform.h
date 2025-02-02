// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectPuzzlePlatform01.h"
#include "Puzzle05BlinkPlatform.generated.h"

/**
 * 
 */
UCLASS()
class UCCH03P01_API APuzzle05BlinkPlatform : public AProjectPuzzlePlatform01
{
	GENERATED_BODY()

public:
	APuzzle05BlinkPlatform();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ToggleTimer = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsActive;

	virtual void BeginPlay() override;
public:

	// 타이머 핸들
	FTimerHandle TimerHandle;



	UFUNCTION()
	void TogglePlatformState();
};
