// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_StaminaCheck_BTService.h"

UAIE_StaminaCheck_BTService::UAIE_StaminaCheck_BTService(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	NodeName = "UAIE_StaminaCheck_BTService";
}

void UAIE_StaminaCheck_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	// check we have a bot character
	if (BotCharacter) {
		// if our max stamina times current stamina low value is greater than our current stamina set stamLow to true else stamLow is false
		bool stamLow = BotCharacter->GetStatMax(1) * (staminaLowValue) > BotCharacter->GetStatValue(1) ? true : false;
		// check we have a blackboard
		if (Blackboard) {
			// get staminaLow key
			FBlackboard::FKey BlackboardKey_StaminaLow = Blackboard->GetKeyID("bStaminaLow");
			// check the key is valid
			if (Blackboard->IsValidKey(BlackboardKey_StaminaLow)) {
				// set the blackboard key
				Blackboard->SetValue<UBlackboardKeyType_Bool>(BlackboardKey_StaminaLow, stamLow);
			}
		}
	}
}