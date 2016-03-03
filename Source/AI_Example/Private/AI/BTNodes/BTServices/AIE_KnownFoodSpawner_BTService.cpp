// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_KnownFoodSpawner_BTService.h"




UAIE_KnownFoodSpawner_BTService::UAIE_KnownFoodSpawner_BTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "Known Spawner Scan";
}

void UAIE_KnownFoodSpawner_BTService::OnSearchStart(FBehaviorTreeSearchData& SearchData) {
	Super::OnSearchStart(SearchData);
	//UBlackboardComponent* BB = SearchData.OwnerComp.GetBlackboardComponent();
	// check we have a blackboard
	if (Blackboard) {
		// get our desired key
		FBlackboard::FKey DesiredObjectKey = Blackboard->GetKeyID("DesiredObject");
		if (Blackboard->IsValidKey(DesiredObjectKey)) {
			// clear our desire key
			Blackboard->SetValue<UBlackboardKeyType_Object>(DesiredObjectKey, NULL);
		}
	}
	
}

void UAIE_KnownFoodSpawner_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	if (Blackboard && BotCharacter && BotController) {
		// get the desire object 
		FBlackboard::FKey DesiredObjectKey = Blackboard->GetKeyID("DesiredObject");
		if (Blackboard->IsValidKey(DesiredObjectKey)) {
			AAIE_BaseFoodSpawner* spawner = NULL;
			// check if we know about any spawners
			if (BotCharacter->knownSpawners.Num() > 0) {
				// check for closest known spawner
				float closestSpawnerDist = NULL;
				for (int32 i = 0; i < BotCharacter->knownSpawners.Num(); ++i) {
					float dist = FVector::Dist(BotCharacter->knownSpawners[i]->GetActorLocation(), BotCharacter->GetActorLocation());
					// if this spawner is closer than any other known spawners set it to the desired spawner
					if (closestSpawnerDist == NULL || dist < closestSpawnerDist) {
						// store the distance of the spawner
						closestSpawnerDist = dist;
						// set the spawner to our spawner refrence
						spawner = BotCharacter->knownSpawners[i];
					}
				}
				// if we found a spawner
				if (spawner != NULL) {
					// set it to our blackboard desired object
					Blackboard->SetValue<UBlackboardKeyType_Object>(DesiredObjectKey, spawner);
				}
				return;
			}
		}

	}

}