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
		// Get the key for the desired stat
		FBlackboard::FKey DesiredStatKey = Blackboard->GetKeyID("lowStat");

		if (Blackboard->IsValidKey(DesiredObjectKey) && Blackboard->IsValidKey(DesiredStatKey)) {
			
			//EBotStatNames DesiredStat = static_cast<EBotStatNames>(Blackboard->GetValue<UBlackboardKeyType_Enum>(DesiredStatKey));
			uint8 DesiredStat = Blackboard->GetValue<UBlackboardKeyType_Enum>(DesiredStatKey);

			AAIE_BaseFoodSpawner* spawner = NULL;
			// check if we know about any spawners
			if (BotCharacter->knownSpawners.Num() > 0) {
				// check for closest known spawner
				float closestSpawnerDist = NULL;
				// check all known spawners
				for (int32 i = 0; i < BotCharacter->knownSpawners.Num(); ++i) {
					// check the spawner can spawn food
					if (BotCharacter->knownSpawners[i]->FoodToSpawn.Num() > 0) {
						// check the food can effect the desired stat
						for (int32 foodSpawnClassIndex = 0; foodSpawnClassIndex < BotCharacter->knownSpawners[i]->FoodToSpawn.Num(); ++foodSpawnClassIndex) {
							// get a ref to the food type
							//AAIE_BaseFood_Actor* classRef = Cast<AAIE_BaseFood_Actor>(BotCharacter->knownSpawners[i]->FoodToSpawn[foodSpawnClassIndex]->GetDefaultObject<AAIE_BaseFood_Actor>());
							AAIE_BaseFood_Actor* classRef = BotCharacter->knownSpawners[i]->FoodToSpawn[foodSpawnClassIndex]->GetDefaultObject<AAIE_BaseFood_Actor>();
							if (classRef != nullptr) {
								// check all the stats it affects for a match
								for (int32 statIndex = 0; statIndex < classRef->Stats.Num(); ++statIndex) {
									// if we have a match
									if (DesiredStat == (uint8)(classRef->Stats[statIndex].Stat)) {
										// check the stat has a positive affect
										if ((classRef->Stats[statIndex].StatChange > 0 && !classRef->Stats[statIndex].bIsInverse) || (classRef->Stats[statIndex].StatChange < 0 && classRef->Stats[statIndex].bIsInverse)) {
											float dist = FVector::Dist(BotCharacter->knownSpawners[i]->GetActorLocation(), BotCharacter->GetActorLocation());
											// if this spawner is closer than any other known spawners set it to the desired spawner
											if (closestSpawnerDist == NULL || dist < closestSpawnerDist) {
												// store the distance of the spawner
												closestSpawnerDist = dist;
												// set the spawner to our spawner refrence
												spawner = BotCharacter->knownSpawners[i];
											}
										}
										

									}
								}
							}
						}

						
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