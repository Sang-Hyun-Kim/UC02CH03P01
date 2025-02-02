// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleSetBase.h"
#include "RotatingPuzzles.generated.h"

/**
 *  회전하는 퍼즐이 있는 퍼즐 계획을 저장할 예정
 */
UCLASS(Blueprintable, BlueprintType)
class UCCH03P01_API URotatingPuzzles : public UPuzzleSetBase
{
	GENERATED_BODY()
public:
	URotatingPuzzles();
};
