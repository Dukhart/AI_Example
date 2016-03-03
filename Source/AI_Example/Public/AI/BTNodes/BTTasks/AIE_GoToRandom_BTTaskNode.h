// Copyright Jordan Duncan 2016

#pragma once

#include "AIE_BTTaskNode.h"
#include "AIE_AIController.h"
#include "AIE_GoToRandom_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_GoToRandom_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()
	// constructor
	UAIE_GoToRandom_BTTaskNode(const FObjectInitializer& ObjectInitializer);
public:
	// execution
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// bool used to force return success of task execution
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	bool bForceSuccess = true;
	// used to determin the search range for our new location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	float searchRadius = 3000.0f;

};
