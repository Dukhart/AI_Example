// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTServices/AIE_BTService.h"
#include "AIE_BotStat_Struct.h"
#include "AIE_StatDesireCheck_BTService.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_StatDesireCheck_BTService : public UAIE_BTService
{
	GENERATED_BODY()
public:
		UAIE_StatDesireCheck_BTService(const FObjectInitializer& ObjectInitializer);
protected:
		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float statLowValue = 50.0f;
};
