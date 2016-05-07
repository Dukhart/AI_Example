// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTTasks/AIE_BTTaskNode.h"
#include "AIE_SetBool_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_SetBool_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()
	
public:
	// constructor
	UAIE_SetBool_BTTaskNode(const FObjectInitializer& ObjectInitializer);
	// execution
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// Cache our key data
	virtual void InitializeFromAsset(UBehaviorTree & Asset) override;

	// the bool key to set
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bool to Set")
		FBlackboardKeySelector BoolToSet;
	// the value to set the bool to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "New Value")
		bool NewValue;
	// holds a ref to a bool key type used to limit assignable keys to only bools
	UBlackboardKeyType_Bool* allowedKey;
	
};
