// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_BTTaskNode.h"

// constructor
UAIE_BTTaskNode::UAIE_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// the default name for our custom BTTask nodes
	NodeName = "AIE_BTTaskNode";
}

// execution
EBTNodeResult::Type UAIE_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	// set the BehaviorTreeComp
	BehaviorTreeCompRef = &OwnerComp;
	if (BehaviorTreeCompRef && BehaviorTreeCompRef->GetBlackboardComponent()) {
		// Set the BlackboardComp
		BlackboardCompRef = BehaviorTreeCompRef->GetBlackboardComponent();
		if (BehaviorTreeCompRef->GetAIOwner()) {
			// Set the Controller
			AIControllerRef = Cast<AAIE_AIController>(BehaviorTreeCompRef->GetAIOwner());
			if (AIControllerRef && AIControllerRef->GetPawn()) {
				// Set the BotCharacter
				BotCharacterRef = Cast<AAIE_BotCharacter>(AIControllerRef->GetPawn());
				// returns succeeded if all components were grabbed
				if (BotCharacterRef) {
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	// returns failed if their was a proplem getting our basic components
	return EBTNodeResult::Failed;
}
