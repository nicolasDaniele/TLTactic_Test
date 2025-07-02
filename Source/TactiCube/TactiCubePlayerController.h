// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "TactiCubePlayerController.generated.h"

UENUM(BlueprintType)
enum class EInputDirectionAxis : uint8
{
	IDA_None	UMETA(DisplayName = "NONE"),
	IDA_Forward UMETA(DisplayName = "FORWARD"),
	IDA_Right	UMETA(DisplayName = "RIGHT")
};	  
	  
/** Forward declaration to improve compiling times */
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class ATactiCubePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATactiCubePlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Input Action for movement */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationKeyboardAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered(const FInputActionValue& InputActionValue);
	void OnSetDestinationReleased();

	UPROPERTY(BlueprintReadOnly)
	EInputDirectionAxis DirectionAxis = EInputDirectionAxis::IDA_None;

private:
	FVector CachedDestination;
	float FollowTime; // For how long it has been pressed
};