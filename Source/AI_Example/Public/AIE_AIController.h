// Copyright Jordan Duncan 2016

#pragma once

#include "AIController.h"
#include "AIE_AIController.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API AAIE_AIController : public AAIController
{
	GENERATED_BODY()

	AAIE_AIController(const FObjectInitializer& ObjectInitializer);
protected:
	// handles what happens when the objet finishes construction
	virtual void BeginPlay() override;
private:
	UBehaviorTree* BehaviorTree;
	UBlackboardData* BlackBoard;
	
};
