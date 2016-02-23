// Copyright Jordan Duncan 2016

#pragma once

#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

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
	// handles what happens when the controller possess a pawn
	virtual void Possess(APawn* InPawn) override;
public:
	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorTreeComp;
	UPROPERTY(transient)
	UBlackboardComponent* BlackBoardComp;
protected:
	// Blackboard keys
	uint8 EnemyKeyId;
	uint8 EnemyLocationId;
};
