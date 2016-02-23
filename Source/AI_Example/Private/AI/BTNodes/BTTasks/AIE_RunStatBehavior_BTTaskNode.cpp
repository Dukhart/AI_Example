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
		FBlackboard::FKey desiredStatKey = Blackboard->GetKeyID("lowStat");
		// check we have a valid key
		if (Blackboard->IsValidKey(desiredStatKey)) {
			// get our keys int value
			int32 behaviorIndex = NULL;
			EBotStatNames statName = static_cast<EBotStatNames>(Blackboard->GetValue<UBlackboardKeyType_Enum>(desiredStatKey));
			// check the int is valid for our array of behavior
			switch (statName) {
			case EBotStatNames::SName_Health:
				behaviorIndex = 0;
				break;
			case EBotStatNames::SName_Stamina:
				behaviorIndex = 1;
				break;
			case EBotStatNames::SName_Hunger:
				behaviorIndex = 2;
				break;
			case EBotStatNames::SName_Happiness:
				behaviorIndex = 3;
				break;
			case EBotStatNames::SName_Strength:
				behaviorIndex = 4;
				break;
			case EBotStatNames::SName_Intelligence:
				behaviorIndex = 5;
				break;
			case EBotStatNames::SName_Speed:
				behaviorIndex = 6;
				break;
			default:
				break;
			}
			if (BotCharacter->BotStatBehavior.IsValidIndex(behaviorIndex)) {
				AIController->BehaviorTreeComp->StopTree();
				AIController->BehaviorTreeComp->StartTree(*BotCharacter->BotStatBehavior[behaviorIndex]);

				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}