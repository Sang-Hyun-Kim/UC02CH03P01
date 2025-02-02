// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleSectorBase.generated.h"

class AProjectPuzzlePlatform01;
class UPuzzleSetBase;
class APuzzle01RotatingPlaform;
UCLASS()
class UCCH03P01_API APuzzleSectorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleSectorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActorSpawnByPuzzleSet(UPuzzleSetBase* set);
	void ClearSector();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Puzzles|Components")
	TArray<TSubclassOf<AProjectPuzzlePlatform01>> PuzzleArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzles|Components")
	TArray<FVector> PuzzleLocations;
	
	TArray<AProjectPuzzlePlatform01*> CurSpawnedPlatforms;
};
