// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TactiCubeCharacter.generated.h"

enum class EInputDirectionAxis : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDirectionChangedSignature, EInputDirectionAxis, NewDirection);

UCLASS(Blueprintable)
class ATactiCubeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATactiCubeCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	FVector GetNextLocation(FVector Direction);

	UPROPERTY(BlueprintAssignable)
	FDirectionChangedSignature OnDirectionChanged;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = GridMovement, meta = (AllowPrivateAccess = "true"))
	class UGridMovementComponent* GridMovement;
};

