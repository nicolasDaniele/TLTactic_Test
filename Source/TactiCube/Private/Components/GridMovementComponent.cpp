#include "Components/GridMovementComponent.h"

UGridMovementComponent::UGridMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FVector UGridMovementComponent::GetNextTargetLocation(FVector Direction)
{
	FVector StartLocation = GetOwner()->GetActorLocation();
	FVector TargetLocation = StartLocation + (Direction.GetSafeNormal() * GridSize);

	return TargetLocation;
}

