// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleManager.generated.h"

class APuzzleSectorBase;
class UPuzzleSetBase;
UCLASS()
class UCCH03P01_API APuzzleManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleManager();

	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void RandomPuzzleGenerator();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// 레벨의 모든 PuzzleSector를 찾아서 추가하는 함수
	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void FindAllPuzzleSectors();

	UFUNCTION(BlueprintCallable, Category = "Puzzles")
	void ClearCurrentPuzzlesFromAllSectors();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|PuzzleSectors")
	TArray<APuzzleSectorBase*> PuzzleSectors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|PuzzleSets")
	TArray<TSubclassOf<UPuzzleSetBase>> PuzzleSets;


	TArray<UPuzzleSetBase*> PuzzleSetObjects;
};
