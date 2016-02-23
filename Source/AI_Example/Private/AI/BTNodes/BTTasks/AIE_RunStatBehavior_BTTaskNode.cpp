// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_RunStatBehavior_BTTaskNode.h"


UAIE_RunStatBehavior_BTTaskNode::UAIE_RunStatBehavior_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}
EBTNodeResult::Type UAIE_RunStatBehavior_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	/*	call super
	*	should aquire refrences for our BehaviorTreeComp, BlackboardComp, AIController, and BotCharacter
	*	will return EBTNodeResult::Succeeded if we have all of them
	*	will return EBTNodeResult::Failed if it failed to grab any of them
	*/
	EBTNodeResult::Type resultFromSuperExecution = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (resultFromSuperExecution == EBTNodeResult::Succeeded) {
		// get the key for our current desired stat
		FBlackboard::FKey desiredStatKey = Blackboard->GetKeyID("DesiredStat");
		// check we have a valid key
		if (Blackboard->IsValidKey(desiredStatKey)) {
			// get our keys int value
			int32 behaviorIndex = Blackboard->GetValue<UBlackboardKeyType_Int>(desiredStatKey);
			// check the int is valid for our array of behavior
			if (BotCharacter->BotStatBehavior.IsValidIndex(behaviorIndex)) {
				AIController->RunBehaviorTree(BotCharacter->BotStatBehavior[behaviorIndex]);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}