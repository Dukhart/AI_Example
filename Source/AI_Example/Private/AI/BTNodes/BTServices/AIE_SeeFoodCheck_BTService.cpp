// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_SeeFoodCheck_BTService.h"




UAIE_SeeFoodCheck_BTService::UAIE_SeeFoodCheck_BTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "See Food Check";
}

void UAIE_SeeFoodCheck_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "start Perception Update Implementation");
	if (Blackboard && BotController) {
		bool bSeeFood = false;
		FBlackboard::FKey seeFoodKey = Blackboard->GetKeyID("bSeeFood");

		TArray<AActor*> Actors;

		BotController->GetAIPerceptionComponent()->GetPerceivedActors(UAISenseConfig_Sight::StaticClass(), Actors);

		for (int aIndex = 0; aIndex < Actors.Num(); ++aIndex) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Perception Update Actor Name = " + Actors[aIndex]->GetName());
			if (Cast<AAIE_BaseFood_Actor>(Actors[aIndex])) {
				bSeeFood = true;
				// break out of the loop its not needed anymore
				break;
			}
		}
		// set blackboard seeFood key to true or false depending on weather we found food
		if (Blackboard->IsValidKey(seeFoodKey)) {
			if (bSeeFood) {
				Blackboard->SetValue<UBlackboardKeyType_Bool>(seeFoodKey, true);
			}
			else {
				Blackboard->SetValue<UBlackboardKeyType_Bool>(seeFoodKey, false);
			}

		}
	}

}