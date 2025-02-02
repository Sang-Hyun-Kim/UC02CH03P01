// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSectorBase.h"
#include "ProjectPuzzlePlatform01.h"
#include "PuzzleSetBase.h"
#include "Puzzle01RotatingPlaform.h"
#include "RotatingPuzzles.h"
// Sets default values
APuzzleSectorBase::APuzzleSectorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PuzzleArray.Add(APuzzle01RotatingPlaform::StaticClass());
	

}

// Called when the game starts or when spawned
void APuzzleSectorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APuzzleSectorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleSectorBase::ActorSpawnByPuzzleSet(UPuzzleSetBase* set)
{
	// 넘겨받은 도면에 대해 랜덤 생성
	if (set->PuzzleLocations.Num() != set->Puzzles.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("퍼즐 개수와 퍼즐 좌표 개수가 맞지 않습니다"));
		return;
	}
	else
	{
		UWorld* pworld = GetWorld();
		if (!pworld)
		{
			UE_LOG(LogTemp, Warning, TEXT("No World Error"));
			return;
		}
		INT32 PuzzleNum = set->Puzzles.Num();
		FTransform CurSectorBaseTransform = GetActorTransform();
		for (int i = 0; i < PuzzleNum; ++i)
		{
			FVector CurPuzzleLocation = CurSectorBaseTransform.GetLocation() + set->PuzzleLocations[i];

			AProjectPuzzlePlatform01* CurPuzzle = pworld->SpawnActor<AProjectPuzzlePlatform01>(
				set->Puzzles[i], CurPuzzleLocation, FRotator::ZeroRotator
			);
			if (CurPuzzle)
			{
				CurSpawnedPlatforms.Add(CurPuzzle);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No PlatformData in Set_Array so No Platform Spawned"));
			}
		}
	}
}

void APuzzleSectorBase::ClearSector()
{
	for (AProjectPuzzlePlatform01* CurSpawnedPlatform : CurSpawnedPlatforms)
	{
		CurSpawnedPlatform->Destroy();
	}
}

