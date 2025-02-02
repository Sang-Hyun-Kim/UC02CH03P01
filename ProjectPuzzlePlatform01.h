// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectPuzzlePlatform01.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UCCH03P01_API AProjectPuzzlePlatform01 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectPuzzlePlatform01();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePosition")
	FVector PRLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzlePosition")
	FVector PRScale;
};
