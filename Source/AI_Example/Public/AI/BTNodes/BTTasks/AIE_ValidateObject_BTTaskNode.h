// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTTasks/AIE_BTTaskNode.h"
#include "AIE_ValidateObject_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_ValidateObject_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()
	
public:
	//Constructor
	UAIE_ValidateObject_BTTaskNode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	//Execution
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	// Cache our key data
	virtual void InitializeFromAsset(UBehaviorTree & Asset) override;

	// The object we are validating
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")
	FBlackboardKeySelector ObjectToValidate;
	// the blackboard key to update the return of the validation
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")
	FBlackboardKeySelector BoolToUpdate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Validation")
	bool bInverseResult;

	// used to limit selectable keys to object key types
	UBlackboardKeyType_Object* ObjectKey;
	// used to limit selectable returns to bool key types
	UBlackboardKeyType_Bool* BoolKey;


};
