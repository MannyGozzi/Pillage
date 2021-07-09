// Copyright Epic Games, Inc. All Rights Reserved.

#include "PillageGameMode.h"
#include "PillageCharacter.h"
#include "UObject/ConstructorHelpers.h"

APillageGameMode::APillageGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
