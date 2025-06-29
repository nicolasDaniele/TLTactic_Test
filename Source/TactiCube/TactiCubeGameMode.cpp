// Copyright Epic Games, Inc. All Rights Reserved.

#include "TactiCubeGameMode.h"
#include "TactiCubePlayerController.h"
#include "TactiCubeCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATactiCubeGameMode::ATactiCubeGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATactiCubePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}