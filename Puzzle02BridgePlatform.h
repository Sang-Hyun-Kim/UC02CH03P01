// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectPuzzlePlatform01.h"
#include "Puzzle02BridgePlatform.generated.h"

/**
 * 
 */
UCLASS()
class UCCH03P01_API APuzzle02BridgePlatform : public AProjectPuzzlePlatform01
{
	GENERATED_BODY()

public:
	APuzzle02BridgePlatform();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComp;

};
