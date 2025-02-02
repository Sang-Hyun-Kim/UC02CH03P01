// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectPuzzlePlatform01.h"
#include "Puzzle01RotatingPlaform.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class UCCH03P01_API APuzzle01RotatingPlaform : public AProjectPuzzlePlatform01
{
	GENERATED_BODY()
public:
	APuzzle01RotatingPlaform();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltatTime) override;

	UFUNCTION()
	virtual void Rotating(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle|RotationSpeed")
	float RotationSpeed;
};
