// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTServices/AIE_BTService.h"
#include "AIE_KnownFoodSpawner_BTService.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_KnownFoodSpawner_BTService : public UAIE_BTService
{
	GENERATED_BODY()
	
public:
	UAIE_KnownFoodSpawner_BTService(const FObjectInitializer& ObjectInitializer);

protected:
		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
		virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData) override;
};
