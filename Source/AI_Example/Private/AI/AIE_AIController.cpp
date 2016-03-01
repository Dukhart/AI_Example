// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_AIController.h"

#include "AIE_BotCharacter.h"

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
	if (BotPawn && BotPawn->BotBehavior) {
		
		if (GetAIPerceptionComponent()) {
			GetPerceptionComponent()->ConfigureSense(*SightConfig);
			// get sight data from pawn
			SightConfig->SightRadius = BotPawn->sightRange;
			SightConfig->LoseSightRadius = (BotPawn->sightRange + BotPawn->sightLossFalloff);
			SightConfig->PeripheralVisionAngleDegrees = BotPawn->sightPeripheralAngle;
			// doesn't appear to currently exist
			// set max age in the editor for now
			//SightConfig->SetMaxAge

			// add event binding for perception
			GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAIE_AIController::AIPerceptionWasUpdated);

			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "HavePerception");
		}else { GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "NoPerception"); }
	}
	
}
void AAIE_AIController::UnPossess() {
	if (GetAIPerceptionComponent()) {
		// remove event binding for perception
		GetPerceptionComponent()->OnPerceptionUpdated.RemoveDynamic(this, &AAIE_AIController::AIPerceptionWasUpdated);
	}

	Super::UnPossess();
}
void AAIE_AIController::AIPerceptionWasUpdated(TArray<AActor*> Actors) {
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red,  "Perception Update call");
	OnPerceptionUpdate(Actors);
}


void AAIE_AIController::OnPerceptionUpdate_Implementation(TArray<AActor*>& Actors) {
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Perception Update Implementation");
}
void AAIE_AIController::UpdateSenseConfig() {
	if (SightConfig) {
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}