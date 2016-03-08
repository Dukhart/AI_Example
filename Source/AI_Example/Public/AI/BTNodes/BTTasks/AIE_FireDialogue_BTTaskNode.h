// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTTasks/AIE_BTTaskNode.h"
#include "AIE_FireDialogue_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_FireDialogue_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()

protected:

	UAIE_FireDialogue_BTTaskNode(const FObjectInitializer& ObjectInitializer);

public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
