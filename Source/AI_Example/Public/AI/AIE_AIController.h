// Copyright Jordan Duncan 2016

#pragma once

#include "AIController.h"

// includes for behavior trees
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
// includes for AI perception
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"
#include "AIE_AISenseConfig_Sight.h"

// interfaces
#include "AIE_AIAnimationInterface.h"

#include "AIE_AIController.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API AAIE_AIController : public AAIController, public IAIE_AIAnimationInterface
{
	GENERATED_BODY()

	AAIE_AIController(const FObjectInitializer& ObjectInitializer);
protected:
	// handles what happens when the objet finishes construction
	virtual void BeginPlay() override;
	// handles what happens when the controller possess a pawn
	virtual void Possess(APawn* InPawn) override;
	// handles what happens when we Unpossess a pawn
	virtual void UnPossess() override;

public:
	UPROPERTY()
	UBehaviorTreeComponent* BehaviorTreeComp;
	UPROPERTY()
	UBlackboardComponent* BlackBoardComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perception")
		UAIE_AISenseConfig_Sight* SightConfig;

	// handle perception update
	UFUNCTION(BlueprintNativeEvent, Category = "Perception")
		void OnPerceptionUpdate(TArray<AActor*>& Actors);
		virtual void OnPerceptionUpdate_Implementation(TArray<AActor*>& Actors);
		//void OnPerceptionUpdate();
		//virtual void OnPerceptionUpdate_Implementation();
	UFUNCTION(BlueprintCallable, Category = "Perception")
			void UpdateSenseConfig();

	UFUNCTION()
	void AIPerceptionWasUpdated(TArray<AActor*> Actors);
protected:
	// Blackboard keys
	uint8 EnemyKeyId;
	uint8 EnemyLocationId;
//INTERFACES
public:
	// animation interface
	void TaskToController_Implementation(EMontageNames eAnimName);
	void ControllerToCharacter_Implementation(EMontageNames eAnimName);
	void CharacterToAnimBp_Implementation(EMontageNames eAnimName);
};
