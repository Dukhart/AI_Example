// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_BTService.h"


UAIE_BTService::UAIE_BTService(const FObjectInitializer& ObjectInittializer)
	: Super(ObjectInittializer) {
	NodeName = "UAIE_BTService";
}

void UAIE_BTService::OnSearchStart(FBehaviorTreeSearchData& SearchData) {
	// assign refs if any are missing 
	// skip assignment if we already have them will save some memory if we have lots of bots running around
	if (!BehaviorTree || !Blackboard || !BotController || !BotCharacter) {
		// set the behavior tree
		BehaviorTree = &SearchData.OwnerComp;
		// check we have the Behavior tree
		Blackboard = BehaviorTree->GetBlackboardComponent();

		// set the bot controller
		BotController = Cast<AAIE_AIController>(SearchData.OwnerComp.GetAIOwner());
		// check we set the bot controller
		if (BotController) {
			// set the bot character
			BotCharacter = Cast<AAIE_BotCharacter>(BotController->GetPawn());
		}
	}
}

void UAIE_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

