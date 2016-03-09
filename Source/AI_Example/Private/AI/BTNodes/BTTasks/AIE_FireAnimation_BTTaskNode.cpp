// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_FireAnimation_BTTaskNode.h"




UAIE_FireAnimation_BTTaskNode::UAIE_FireAnimation_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "Fire Animation";

	eAnimToPlay = EMontageNames::None;
}

EBTNodeResult::Type UAIE_FireAnimation_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	if (result == EBTNodeResult::Succeeded && eAnimToPlay != EMontageNames::None && AIController->Implements<UAIE_AIAnimationInterface>()) {
		IAIE_AIAnimationInterface::Execute_TaskToController(AIController, eAnimToPlay);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}