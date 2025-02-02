// Copyright Epic Games, Inc. All Rights Reserved.

#include "UCCH03P01GameMode.h"
#include "UCCH03P01Character.h"
#include "UObject/ConstructorHelpers.h"

AUCCH03P01GameMode::AUCCH03P01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
