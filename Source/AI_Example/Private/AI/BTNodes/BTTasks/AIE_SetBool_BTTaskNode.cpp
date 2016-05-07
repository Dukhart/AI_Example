// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_SetBool_BTTaskNode.h"




// constructor
UAIE_SetBool_BTTaskNode::UAIE_SetBool_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// set the default node name
	NodeName = "Set Bool";

	// array to hold valid key types
	TArray<UBlackboardKeyType*> keyTypes;
	// init the bool key type
	allowedKey = CreateDefaultSubobject<UBlackboardKeyType_Bool>("Allowed Key");

	if (allowedKey != nullptr) {
		// add the bool key type to the array
		keyTypes.Add(allowedKey);
		// set the allowed types of our key selector
		BoolToSet.AllowedTypes = keyTypes;
	}
}
// Cache our key data
void UAIE_SetBool_BTTaskNode::InitializeFromAsset(UBehaviorTree& Asset) {
	Super::InitializeFromAsset(Asset);
	// Cache the Instance of the key from the blackboard
	BoolToSet.CacheSelectedKey(Asset.BlackboardAsset);
}
// execution
EBTNodeResult::Type UAIE_SetBool_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	// check we have a blackboard ref and our key is valid
	if (Blackboard != nullptr && Blackboard->IsValidKey(BoolToSet.GetSelectedKeyID())) {
	//if (Blackboard != nullptr) {
		// set the black board key value
		Blackboard->SetValue<UBlackboardKeyType_Bool>(BoolToSet.GetSelectedKeyID() , NewValue);
		// return success
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Set Bool Success");
		return EBTNodeResult::Succeeded;
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Set Bool FAILED");
	return EBTNodeResult::Failed;
}