// Copyright Epic Games, Inc. All Rights Reserved.

#include "TactiCubePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "TactiCubeCharacter.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

#include "TactiCubeCharacter.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ATactiCubePlayerController::ATactiCubePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;


}

void ATactiCubePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationKeyboardAction, ETriggerEvent::Started, this, &ATactiCubePlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationKeyboardAction, ETriggerEvent::Triggered, this, &ATactiCubePlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationKeyboardAction, ETriggerEvent::Completed, this, &ATactiCubePlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationKeyboardAction, ETriggerEvent::Canceled, this, &ATactiCubePlayerController::OnSetDestinationReleased);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ATactiCubePlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void ATactiCubePlayerController::OnSetDestinationTriggered(const FInputActionValue& InputActionValue)
{
	FVector Direction = InputActionValue.Get<FVector>();

	DirectionAxis = FMath::Abs(Direction.Y) > FMath::Abs(Direction.X) ?
		EInputDirectionAxis::IDA_Right : EInputDirectionAxis::IDA_Forward;

	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	if (ATactiCubeCharacter* TCCharacter = Cast<ATactiCubeCharacter>(GetPawn()))
	{
		CachedDestination = DirectionAxis == EInputDirectionAxis::IDA_Forward ?
			TCCharacter->GetNextLocation(FVector(Direction.X, 0.f, 0.f)) :
			TCCharacter->GetNextLocation(FVector(0.f, Direction.Y, 0.f));
	}
	else return;

	// Move towards next grid position
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ATactiCubePlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}

	FollowTime = 0.f;
	DirectionAxis = EInputDirectionAxis::IDA_None;
}