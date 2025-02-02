// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectPuzzlePlatform01.h"
#include "Puzzle03RotatingLog.generated.h"

/**
 * 
 */
UCLASS()
class UCCH03P01_API APuzzle03RotatingLog : public AProjectPuzzlePlatform01
{
	GENERATED_BODY()

public:
	APuzzle03RotatingLog();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Root;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltatTime) override;

	UFUNCTION()
	virtual void RotatingRoot(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle|RotationSpeed")
	float RotationSpeed;
};
