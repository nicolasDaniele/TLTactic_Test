#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushableActor.generated.h"

class UGridMovementComponent;
class UBoxComponent;
class UPhysicsConstraintComponent;

UCLASS()
class TACTICUBE_API APushableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APushableActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPhysicsConstraintComponent* PhysicsConstraint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* XAxixCollider;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* YAxixCollider;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UGridMovementComponent* GridMovement;
};
