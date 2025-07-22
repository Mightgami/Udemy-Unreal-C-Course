// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealProjectCGameMode.h"
#include "UnrealProjectCCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealProjectCGameMode::AUnrealProjectCGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
