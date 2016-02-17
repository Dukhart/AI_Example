// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTTasks/AIE_BTTaskNode.h"
#include "AIE_UseItem_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_UseItem_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()

public:
		// constructor
		UAIE_UseItem_BTTaskNode(const FObjectInitializer &ObjectInitializer);
		// executes the task when called
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// the max distance at which we can reach an item
		float MaxReach = 300.0f;
};
