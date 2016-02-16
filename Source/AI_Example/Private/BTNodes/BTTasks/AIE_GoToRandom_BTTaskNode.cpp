// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_GoToRandom_BTTaskNode.h"

#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


// constructor
UAIE_GoToRandom_BTTaskNode::UAIE_GoToRandom_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// default name for our node
	NodeName = "Go To Random";
}

// execution
EBTNodeResult::Type UAIE_GoToRandom_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	/*	call super 
	 *	should aquire refrences for our BehaviorTreeComp, BlackboardComp, AIController, and BotCharacter
	 *	will return EBTNodeResult::Succeeded if we have all of them
	 *	will return EBTNodeResult::Failed if it failed to grab any of them
	*/
	EBTNodeResult::Type resultFromSuperExecution = Super::ExecuteTask(OwnerComp, NodeMemory);
	// check that we successfully grabbed the BehaviorTreeComp, BlackboardComp, AIController, and BotCharacter
	if (resultFromSuperExecution == EBTNodeResult::Succeeded) {
		// check that we can get the World
		if (GetWorld()) {
			// get the current nav system from the world
			UNavigationSystem* navSystem = UNavigationSystem::GetCurrent(GetWorld());
			// check that we have a nav system
			if (navSystem) {
				// get our actors current location to pe used as our start position
				FVector startPosi = BotCharacterRef->GetActorLocation();
				// create a nav location to be used as our end position 
				// default will be set to our current position in case of failure to find a suitable end position
				FNavLocation endPosi = FNavLocation(startPosi);
				// attempt to get a random new position
				if (navSystem->GetRandomReachablePointInRadius(startPosi, searchRadius, endPosi)) {
					// if we were successfull in finding a new location get the MoveToLocation BlackboardKeyID
					FBlackboard::FKey BlackboardKey_MoveToLocation = BlackboardCompRef->GetKeyID("MoveToLocation");
					// check that we got the key
					if ( BlackboardCompRef->IsValidKey( BlackboardKey_MoveToLocation)) {
						// set the MoveToLocation BlackboardKeyID to our new location
						BlackboardCompRef->SetValue<UBlackboardKeyType_Vector>(BlackboardKey_MoveToLocation, endPosi.Location);
						// return succeeded now that we have set up our new loacation
						return EBTNodeResult::Succeeded;
					}
					else {
						// return Aborted if we can't find the Key as it will never succeed without a proper Key
						if (bForceSuccess) {
							return EBTNodeResult::Succeeded;
						}
						return EBTNodeResult::Aborted;
					}
				}
				// return in progress if their are currently no valid locations
				if (bForceSuccess) {
					return EBTNodeResult::Succeeded;
				}
				return EBTNodeResult::InProgress;
			}
		}
		 
		
	}
	// we will only get here if execution fails so we will check if force success is on
	if (bForceSuccess) {
		// if force success is on we will return Succeeded anyway
		return EBTNodeResult::Succeeded;
	}
	// we want to return Failed after the force success check
	return EBTNodeResult::Failed;
}