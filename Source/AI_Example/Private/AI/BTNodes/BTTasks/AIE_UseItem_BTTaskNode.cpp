// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_UseItem_BTTaskNode.h"

#include "AIE_IsUsable.h"
#include "AIE_StaticLibrary.h"

// constructor
UAIE_UseItem_BTTaskNode::UAIE_UseItem_BTTaskNode(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "Use Item";
}

// executes the task when called
EBTNodeResult::Type UAIE_UseItem_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	/*	call super
	*	should aquire refrences for our BehaviorTreeComp, BlackboardComp, AIController, and BotCharacter
	*	will return EBTNodeResult::Succeeded if we have all of them
	*	will return EBTNodeResult::Failed if it failed to grab any of them
	*/
	EBTNodeResult::Type resultFromSuperExecution = Super::ExecuteTask(OwnerComp, NodeMemory);
	// check that we successfully grabbed the BehaviorTreeComp, BlackboardComp, AIController, and BotCharacter
	// check that our bot implements the is Usable interface
	if (resultFromSuperExecution == EBTNodeResult::Succeeded && BotCharacter->GetClass()->ImplementsInterface(UAIE_IsUsable::StaticClass())) {
		// get our object from blackboard key
		FBlackboard::FKey DesiredObjectKey = Blackboard->GetKeyID("DesiredObject");
		// check that our key is valid
		if (Blackboard->IsValidKey(DesiredObjectKey)) {
			// store our object as an actor
			AActor* desiredObjectActor = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(DesiredObjectKey));
			// get the distance from our object
			float distance = FVector::Dist(desiredObjectActor->GetActorLocation(), BotCharacter->GetActorLocation());
			// compare distance to max reach
			if (distance <= MaxReach) {
				// array of actors to ignore
				TArray<AActor*> actorsToIgnore;
				// the bot can't get in the way of itself
				actorsToIgnore.Add(BotCharacter);
				// will hold our hit result
				
				FHitResult hit;
				// fire the trace and check if we hit something
				
				if (UAIE_StaticLibrary::Trace(GetWorld(), actorsToIgnore, BotCharacter->GetActorLocation(), desiredObjectActor->GetActorLocation(), hit, ECollisionChannel::ECC_WorldDynamic, false, true)) {
#if !UE_BUILD_SHIPPING
					GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, hit.GetActor()->GetName() + "  grab object");
#endif
					if (hit.GetActor() == desiredObjectActor) {
#if !UE_BUILD_SHIPPING
						GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotCharacter->BotName.ToString() + " trying to grab object");
#endif
							// exacute AI_UseItem on our bot with the Desired object
							IAIE_IsUsable::Execute_AI_ActivateUseItem(BotCharacter, desiredObjectActor);
							// return success
							return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}
	// return failed
	return EBTNodeResult::Failed;
}
