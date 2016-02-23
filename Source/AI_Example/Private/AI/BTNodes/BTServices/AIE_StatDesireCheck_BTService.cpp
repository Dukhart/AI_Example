// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_StatDesireCheck_BTService.h"



UAIE_StatDesireCheck_BTService::UAIE_StatDesireCheck_BTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}
void UAIE_StatDesireCheck_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}