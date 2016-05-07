// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTTasks/AIE_BTTaskNode.h"

#include "AIE_SetMoveSpeed_BTTaskNode.generated.h"




/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_SetMoveSpeed_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()
	
public:
	//Constructor
	UAIE_SetMoveSpeed_BTTaskNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// Execution
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Speed")
		float NewValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Speed")
	EMoveMode ModeToChange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move Speed")
	EMoveProperty PropertyToChange;


};
