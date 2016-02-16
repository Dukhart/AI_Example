// Copyright Jordan Duncan 2016

#pragma once

#include "BehaviorTree/BTService.h"

// required to access AICharacters and their controllers
#include "AIE_AIController.h"
#include "AIE_BotCharacter.h"
// required to access blackboard keys
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

#include "AIE_BTService.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_BTService : public UBTService
{
	GENERATED_BODY()

public:
	// constructor
	UAIE_BTService(const FObjectInitializer& ObjectInittializer);
protected:
	// handles tick events
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	// The behavior tree tied to this node
	UBehaviorTreeComponent* BehaviorTree;
	// The blackboard tree tied to this node
	UBlackboardComponent* Blackboard;
	// The bot controller tree tied to this node
	AAIE_AIController* BotController;
	// The bot character tied to this node
	AAIE_BotCharacter* BotCharacter;

};
