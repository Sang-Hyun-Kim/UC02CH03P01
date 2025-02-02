// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectPuzzlePlatform01.h"

// Sets default values
AProjectPuzzlePlatform01::AProjectPuzzlePlatform01()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PRLocation = FVector(0,0,0);
}

// Called when the game starts or when spawned
void AProjectPuzzlePlatform01::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectPuzzlePlatform01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

