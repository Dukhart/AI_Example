// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_SetMoveSpeed_BTTaskNode.h"




UAIE_SetMoveSpeed_BTTaskNode::UAIE_SetMoveSpeed_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "SetMoveProperty";
}
// Execution
EBTNodeResult::Type UAIE_SetMoveSpeed_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (BotCharacter != nullptr && BotCharacter->GetMovementComponent() != nullptr) {
		UCharacterMovementComponent* MoveCompRef = Cast<UCharacterMovementComponent>(BotCharacter->GetMovementComponent());
		// Make Sure we have the movement comp ref
		if (MoveCompRef != nullptr) {
			switch(PropertyToChange) {

			case EMoveProperty::Acceleration:
				MoveCompRef->MaxAcceleration = NewValue;
				break;
			case EMoveProperty::Gravity:
				MoveCompRef->GravityScale = NewValue;
				break;
			case EMoveProperty::Mass:
				MoveCompRef->Mass = NewValue;
				break;
			case EMoveProperty::MaxSpeed:
				
				switch (ModeToChange) {
				case EMoveMode::ALL:
					MoveCompRef->MaxFlySpeed = NewValue;
					MoveCompRef->MaxWalkSpeed = NewValue;
					MoveCompRef->MaxSwimSpeed = NewValue;
					MoveCompRef->JumpZVelocity = NewValue;
					break;
				case EMoveMode::Flying:
					MoveCompRef->MaxFlySpeed = NewValue;
					break;
				case EMoveMode::Jumping:
					MoveCompRef->JumpZVelocity = NewValue;
					break;
				case EMoveMode::Swimming:
					MoveCompRef->MaxSwimSpeed = NewValue;
					break;
				case EMoveMode::Walking:
					MoveCompRef->MaxWalkSpeed = NewValue;
					break;
				default:
					break;
				}

				break;
				default:
					break;
			}
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}