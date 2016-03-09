// Copyright Jordan Duncan 2016

#pragma once

#include "AI/BTNodes/BTTasks/AIE_BTTaskNode.h"

// interfaces
#include "AIE_AIAnimationInterface.h"

#include "AIE_FireAnimation_BTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_FireAnimation_BTTaskNode : public UAIE_BTTaskNode
{
	GENERATED_BODY()
	
protected:

	UAIE_FireAnimation_BTTaskNode(const FObjectInitializer& ObjectInitializer);

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	EMontageNames eAnimToPlay;

	/*
	//INTERFACES
public:
	// animation interface
	
	void TaskToController_Implementation(EMontageNames eAnimName);
	void ControllerToCharacter_Implementation(EMontageNames eAnimName);
	void CharacterToAnimBp_Implementation(EMontageNames eAnimName);
	*/
	
};
