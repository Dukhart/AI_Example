// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_FireDialogue_BTTaskNode.h"




UAIE_FireDialogue_BTTaskNode::UAIE_FireDialogue_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "FireDialog";
}

EBTNodeResult::Type UAIE_FireDialogue_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	// will be succeeded if we have a blackboard, behaviorTree, botcharacter and bot controller
	if (result == EBTNodeResult::Succeeded) {
		// get our desired object key
		FBlackboard::FKey desiredObjectKey = Blackboard->GetKeyID("DesiredObject");
		// make sure we have a valid key
		if (desiredObjectKey && Blackboard->IsValidKey(desiredObjectKey)){
			// get a ref to our desired object actor
			AActor* desiredObjectRef = Cast<AActor>(Blackboard->GetValue<UBlackboardKeyType_Object>(desiredObjectKey));
			// check we successfully cast
			if (desiredObjectRef) {
				// call our bots dialog
				BotCharacter->DialogCallout(desiredObjectRef);
				result = EBTNodeResult::Succeeded;
				return result;
			}
		}
	}
	result = EBTNodeResult::Failed;
	return result;
}