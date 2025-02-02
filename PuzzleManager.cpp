// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleManager.h"
#include "Engine/World.h"
#include "PuzzleSectorBase.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleSetBase.h"
#include "RotatingPuzzles.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
APuzzleManager::APuzzleManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APuzzleManager::RandomPuzzleGenerator()
{
    if (PuzzleSetObjects.Num() == 0 || PuzzleSectors.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("등록된 퍼즐 섹터가 없거나 퍼즐 종류가 없습니다."));
        return;
    }
    for (APuzzleSectorBase* Sector : PuzzleSectors)
    {
        // 매니저가 보관중인 도안 객체중 하나를 랜덤으로 선택해 생성
        int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, PuzzleSetObjects.Num() - 1);
        UPuzzleSetBase* SelectedPuzzleClass = PuzzleSetObjects[RandomIndex];
   
        if (SelectedPuzzleClass)
        {
            Sector->ActorSpawnByPuzzleSet(SelectedPuzzleClass);
        }
    }

}

// Called when the game starts or when spawned
void APuzzleManager::BeginPlay()
{
	Super::BeginPlay();

    // 등록된 Set이 있는지 확인
    // 등록된 퍼즐 도안에 대한 객체 생성후 Manager 에서 보관
    if (PuzzleSets.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("등록된 퍼즐 섹터가 없거나 퍼즐 종류가 없습니다."));
        return;
    }
    else
    {
        for (TSubclassOf<UPuzzleSetBase> PuzzleSet : PuzzleSets)
        {
            UPuzzleSetBase* NewPuzzleSetObject = NewObject<UPuzzleSetBase>(this, PuzzleSet);
            PuzzleSetObjects.Add(NewPuzzleSetObject);
        }
    }

    FindAllPuzzleSectors(); // 레벨에 배치된 모든 퍼즐 구역 객체들을 찾아 등록하기
    RandomPuzzleGenerator(); // 등록된 퍼즐로 랜덤 퍼즐 생성
}

void APuzzleManager::FindAllPuzzleSectors()
{
    PuzzleSectors.Empty(); // 기존 목록 초기화

    TArray<AActor*> LevelPuzzleSectors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzleSectorBase::StaticClass(), LevelPuzzleSectors);

    for (AActor* PuzzleSector : LevelPuzzleSectors)
    {
        APuzzleSectorBase* Sector = Cast<APuzzleSectorBase>(PuzzleSector);
        if (Sector)
        {
            PuzzleSectors.Add(Sector);
        }
    }

}

void APuzzleManager::ClearCurrentPuzzlesFromAllSectors()
{

    if ( PuzzleSectors.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("등록된 퍼즐 섹터가 없습니다."));
        return;
    }
    else
    {
        for (APuzzleSectorBase* Sector : PuzzleSectors)
        {
            Sector->ClearSector();
        }
    }
}