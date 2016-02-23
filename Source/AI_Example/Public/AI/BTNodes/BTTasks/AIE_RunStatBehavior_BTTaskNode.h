// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTTasks/AIE_BTTaskNode.h"
#include "AIE_RunStatBehavior_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_RunStatBehavior_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()
		// constructor
		UAIE_RunStatBehavior_BTTaskNode(const FObjectInitializer& ObjectInitializer);
public:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
