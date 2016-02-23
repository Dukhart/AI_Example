// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTServices/AIE_BTService.h"
#include "AIE_StaminaCheck_BTService.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_StaminaCheck_BTService : public UAIE_BTService
{
	GENERATED_BODY()
public:
	// constructor
	UAIE_StaminaCheck_BTService(const FObjectInitializer& ObjectInitializer);
protected:
	// handles tick events
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	// should range from 0 to 1 represents percent of stamina that is left before triggering staminaLow blackBoardKey
	// example 0.5f would be 50% stamina drain before triggering staminaLow blackBoardKey
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float staminaLowValue = 0.5f;
};
