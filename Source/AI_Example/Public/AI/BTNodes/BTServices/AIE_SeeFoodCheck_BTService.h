// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTServices/AIE_BTService.h"
#include "AIE_SeeFoodCheck_BTService.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_SeeFoodCheck_BTService : public UAIE_BTService
{
	GENERATED_BODY()
public:
	UAIE_SeeFoodCheck_BTService(const FObjectInitializer& ObjectInitializer);

protected:
		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
