// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_RunBaseBehavior_BTTaskNode.h"




UAIE_RunBaseBehavior_BTTaskNode::UAIE_RunBaseBehavior_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}
EBTNodeResult::Type UAIE_RunBaseBehavior_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	/*	call super
	*	should aquire refrences for our BehaviorTreeComp, BlackboardComp, AIController, and BotCharacter
	*	will return EBTNodeResult::Succeeded if we have all of them
	*	will return EBTNodeResult::Failed if it failed to grab any of them
	*/
	EBTNodeResult::Type resultFromSuperExecution = Super::ExecuteTask(OwnerComp, NodeMemory);

	if (resultFromSuperExecution == EBTNodeResult::Succeeded) {
		if (BotCharacter->BotBehavior) {
			FBlackboard::FKey lowStatEnumKey = Blackboard->GetKeyID("lowStat");

			if (Blackboard->IsValidKey(lowStatEnumKey)) {
				Blackboard->SetValue<UBlackboardKeyType_Enum>(lowStatEnumKey, static_cast<UBlackboardKeyType_Enum::FDataType>(EBotStatNames::SName_None));
			}
			AIController->BehaviorTreeComp->StopTree();
			AIController->BehaviorTreeComp->StartTree(*BotCharacter->BotBehavior);
			
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}