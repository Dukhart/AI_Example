// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_AIController.h"

#include "AIE_BotCharacter.h"

AAIE_AIController::AAIE_AIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Comp");
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Comp");
}
void AAIE_AIController::BeginPlay() {
	Super::BeginPlay();
}
void AAIE_AIController::Possess(APawn* InPawn) {
	Super::Possess(InPawn);

	AAIE_BotCharacter* BotPawn = Cast<AAIE_BotCharacter>(InPawn);
	if (BotPawn && BotPawn->BotBehavior) {
		// get the black board from the pawn behavior tree
		BlackBoardComp->InitializeBlackboard(*(BotPawn->BotBehavior->BlackboardAsset));
		// Get keys from blackboard

		// start the behvior tree from the pawn
		BehaviorTreeComp->StartTree(*(BotPawn->BotBehavior));

	}
}