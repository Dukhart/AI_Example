// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_AIController.h"
#include "AIE_BotCharacter.h"

#include "AIE_BaseFood_Actor.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AAIE_AIController::AAIE_AIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

	// make behavior tree component
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Comp");
	// make blackboard component
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Comp");
	// make the perception component
	UAIPerceptionComponent* aiPerceptionRef = CreateDefaultSubobject<UAIPerceptionComponent>("Perception Comp");
	// set the perception component
	SetPerceptionComponent(*aiPerceptionRef);
	// make our sight config to be used for our ai's sense of sight
	SightConfig = CreateDefaultSubobject<UAIE_AISenseConfig_Sight>("Sight Config");
	// make sure we succefully made and assigned our perception comp and made our Sight Configuration
	if (GetPerceptionComponent() && SightConfig) {
		// set detection
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		// set max age requires making a child class of the sense
		SightConfig->SetMaxAge(3.0f);

		// add sight to our perception
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
		// set sight to be our dominant sense
		GetPerceptionComponent()->SetDominantSense(SightConfig->GetSenseImplementation());

	}


}
void AAIE_AIController::BeginPlay() {
	Super::BeginPlay();
}
void AAIE_AIController::Possess(APawn* InPawn) {
	Super::Possess(InPawn);

	AAIE_BotCharacter* BotPawn = Cast<AAIE_BotCharacter>(InPawn);
	if (BotPawn) {

		if (GetAIPerceptionComponent()) {
			GetPerceptionComponent()->ConfigureSense(*SightConfig);
			// get sight data from pawn
			SightConfig->SightRadius = BotPawn->sightRange;
			SightConfig->LoseSightRadius = (BotPawn->sightRange + BotPawn->sightLossFalloff);
			SightConfig->PeripheralVisionAngleDegrees = BotPawn->sightPeripheralAngle;
			// binds the perception update function to call our custom perception update behavior
			GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAIE_AIController::AIPerceptionWasUpdated);
		}
		
	}

}
void AAIE_AIController::UnPossess() {
	if (GetAIPerceptionComponent()) {
		// remove event binding for perception
		//GetPerceptionComponent()->OnPerceptionUpdated.RemoveDynamic(this, &AAIE_AIController::AIPerceptionWasUpdated);
	}

	Super::UnPossess();
}
void AAIE_AIController::AIPerceptionWasUpdated(TArray<AActor*> Actors) {
	// call our blueprint native event
	// seems to cause errors if we bind the native event directly to OnPerceptionUpdate
	// hence the nested function call
	OnPerceptionUpdate(Actors);
}

// handles perception updated
void AAIE_AIController::OnPerceptionUpdate_Implementation(TArray<AActor*>& Actors) {
	for (int aIndex = 0; aIndex < Actors.Num(); ++aIndex) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Perception Update Actor Name = " + Actors[aIndex]->GetName());
		AAIE_BaseFoodSpawner* spawnerRef = Cast<AAIE_BaseFoodSpawner>(Actors[aIndex]);
		if (spawnerRef) {
			AAIE_BotCharacter* botRef = Cast<AAIE_BotCharacter>(GetPawn());
			if (botRef) {
				botRef->knownSpawners.AddUnique(spawnerRef);
				if (botRef->knownSpawners.Num() > botRef->maxKnownSpawners && botRef->maxKnownSpawners != 0) {
					botRef->knownSpawners.RemoveAt(0);
				}
			}
		}
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "start Perception Update Implementation");
	/*
	if (BlackBoardComp) {
		bool bSeeFood = false;
		FBlackboard::FKey seeFoodKey = BlackBoardComp->GetKeyID("bSeeFood");
		for (int aIndex = 0; aIndex < Actors.Num(); ++aIndex) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Perception Update Actor Name = " + Actors[aIndex]->GetName());
			if (Cast<AAIE_BaseFood_Actor>(Actors[aIndex])) {
				bSeeFood = true;
				// break out of the loop its not needed anymore
				break;
			}
		}
		// set blackboard seeFood key to true or false depending on weather we found food
		if (BlackBoardComp->IsValidKey(seeFoodKey)) {
			if (bSeeFood) {
				BlackBoardComp->SetValue<UBlackboardKeyType_Bool>(seeFoodKey, true);
			}
			else {
				BlackBoardComp->SetValue<UBlackboardKeyType_Bool>(seeFoodKey, false);
			}

		}
	}
	*/
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "end Perception Update Implementation");
}
void AAIE_AIController::UpdateSenseConfig() {
	if (SightConfig) {
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

// INTERFACES
// AIAnimation Interface
void AAIE_AIController::TaskToController_Implementation(EMontageNames eAnimName) {
	if (GetPawn() && GetPawn()->Implements<UAIE_AIAnimationInterface>()) {
		IAIE_AIAnimationInterface::Execute_ControllerToCharacter(GetPawn(), eAnimName);
	}
}
void AAIE_AIController::ControllerToCharacter_Implementation(EMontageNames eAnimName) {

}
void AAIE_AIController::CharacterToAnimBp_Implementation(EMontageNames eAnimName) {

}