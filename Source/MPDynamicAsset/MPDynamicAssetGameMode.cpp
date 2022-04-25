// Copyright Epic Games, Inc. All Rights Reserved.

#include "MPDynamicAssetGameMode.h"
#include "MPDynamicAssetCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMPDynamicAssetGameMode::AMPDynamicAssetGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
