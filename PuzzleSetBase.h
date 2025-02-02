// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PuzzleSetBase.generated.h"

class AProjectPuzzlePlatform01;
/**
 *  퍼즐 종류의 핵심이 될 Interface
 */
UCLASS(Blueprintable, BlueprintType)
class UCCH03P01_API UPuzzleSetBase : public UObject
{
	GENERATED_BODY()
public:
	UPuzzleSetBase();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles")
	TArray<TSubclassOf<AProjectPuzzlePlatform01>> Puzzles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlesLocations")
	TArray<FVector> PuzzleLocations;
};
