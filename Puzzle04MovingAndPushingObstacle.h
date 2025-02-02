// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectPuzzlePlatform01.h"
#include "Puzzle04MovingAndPushingObstacle.generated.h"

/**
 * 
 */
UCLASS()
class UCCH03P01_API APuzzle04MovingAndPushingObstacle : public AProjectPuzzlePlatform01
{
	GENERATED_BODY()
public:
	APuzzle04MovingAndPushingObstacle();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Root;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void Moving();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle|MovementSpeed")
    float MovementSpeed = 200.0f;

	int movementflag = 1;

    /** 이동 간격 (타이머 주기) */
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveInterval = 0.5f; // 0.02초마다 이동

    /** 왕복 거리 */
    UPROPERTY(EditAnywhere, Category = "Movement")
    float TravelDistance = 500.0f; // 500 유닛 왕복

    /** 이동 방향 */
    FVector MoveDirection = FVector(0.0f, 0.0f, 1.0f); // X축 방향 이동

    /** 시작 위치 */
    FVector StartLocation;

    /** 타이머 핸들 */
    FTimerHandle MoveTimerHandle;
};
