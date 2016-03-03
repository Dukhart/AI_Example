// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_BTTaskNode.h"

// constructor
UAIE_BTTaskNode::UAIE_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// the default name for our custom BTTask nodes
	NodeName = "AIE_BTTaskNode";
	bCreateNodeInstance = true;
}

// execution
EBTNodeResult::Type UAIE_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	// set the BehaviorTreeComp
	BehaviorTree = &OwnerComp;
	if (BehaviorTree && BehaviorTree->GetBlackboardComponent()) {
		// Set the BlackboardComp
		Blackboard = BehaviorTree->GetBlackboardComponent();
		if (BehaviorTree->GetAIOwner()) {
			// Set the Controller
			AIController = Cast<AAIE_AIController>(BehaviorTree->GetAIOwner());
			if (AIController && AIController->GetPawn()) {
				// Set the BotCharacter
				BotCharacter = Cast<AAIE_BotCharacter>(AIController->GetPawn());
				// returns succeeded if all components were grabbed
				if (BotCharacter) {
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	// returns failed if their was a proplem getting our basic components
	return EBTNodeResult::Failed;
}
