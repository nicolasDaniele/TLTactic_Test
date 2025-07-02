#include "Actors/PushableActor.h"
#include "Components/GridMovementComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/BoxComponent.h"

APushableActor::APushableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetLinearDamping(3.f);
	SetRootComponent(StaticMesh);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>("PhysicsContraint");
	PhysicsConstraint->SetupAttachment(StaticMesh);
	FConstrainComponentPropName CompName = FConstrainComponentPropName();
	CompName.ComponentName = FName("StaticMesh");
	PhysicsConstraint->ComponentName1 = CompName;
	PhysicsConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Free, 0.f);
	PhysicsConstraint->SetLinearYLimit(ELinearConstraintMotion::LCM_Free, 0.f);
	PhysicsConstraint->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	PhysicsConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 45.f);
	PhysicsConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 45.f);
	PhysicsConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 45.f);

	XAxixCollider = CreateDefaultSubobject<UBoxComponent>("XAxixCollider");
	XAxixCollider->SetupAttachment(StaticMesh);

	YAxixCollider = CreateDefaultSubobject<UBoxComponent>("YAxixCollider");
	YAxixCollider->SetupAttachment(StaticMesh);

	GridMovement = CreateDefaultSubobject<UGridMovementComponent>("GridMovement");
}