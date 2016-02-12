// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_AIController.h"



AAIE_AIController::AAIE_AIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	//BehaviorTree = 
}
void AAIE_AIController::BeginPlay() {
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
}