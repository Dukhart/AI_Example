// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_KnownFoodSpawner_BTService.h"




UAIE_KnownFoodSpawner_BTService::UAIE_KnownFoodSpawner_BTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "Known Spawner Scan";
}

void UAIE_KnownFoodSpawner_BTService::OnSearchStart(FBehaviorTreeSearchData& SearchData) {
	
	UBlackboardComponent* BB = SearchData.OwnerComp.GetBlackboardComponent();

	if (BB) {
		FBlackboard::FKey DesiredObjectKey = BB->GetKeyID("DesiredObject");
		if (BB->IsValidKey(DesiredObjectKey)) {
			BB->SetValue<UBlackboardKeyType_Object>(DesiredObjectKey, NULL);
		}
	}
	
	Super::OnSearchStart(SearchData);
}

void UAIE_KnownFoodSpawner_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (Blackboard && BotCharacter && BotController) {
		FBlackboard::FKey DesiredObjectKey = Blackboard->GetKeyID("DesiredObject");
		if (Blackboard->IsValidKey(DesiredObjectKey)) {
			AAIE_BaseFoodSpawner* spawner = NULL;
			// check for closest known spawner
			if (BotCharacter->knownSpawners.Num() > 0) {
				float closestSpawnerDist = NULL;
				for (int32 i = 0; i < BotCharacter->knownSpawners.Num(); ++i) {
					float dist = FVector::Dist(BotCharacter->knownSpawners[i]->GetActorLocation(), BotCharacter->GetActorLocation());
					if (closestSpawnerDist != NULL || dist < closestSpawnerDist) {
						closestSpawnerDist = dist;
						spawner = BotCharacter->knownSpawners[i];
					}
				}
				if (spawner != NULL) {
					Blackboard->SetValue<UBlackboardKeyType_Object>(DesiredObjectKey, spawner);
				}
				return;
			}
		}

	}

}