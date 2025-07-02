#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridMovementComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TACTICUBE_API UGridMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UGridMovementComponent();

	UFUNCTION(BlueprintCallable)
	FVector GetNextTargetLocation(FVector Direction);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float GridSize = 200.f;
};
