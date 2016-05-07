// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_ValidateObject_BTTaskNode.h"



// Constructor
UAIE_ValidateObject_BTTaskNode::UAIE_ValidateObject_BTTaskNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "Validate Object";

	TArray<UBlackboardKeyType*> AllowedKeys;

	ObjectKey = CreateDefaultSubobject<UBlackboardKeyType_Object>("Object Key");
	BoolKey = CreateDefaultSubobject<UBlackboardKeyType_Bool>("Bool Key");

	// limit the object to validate to accept object key types only
	if (ObjectKey != nullptr) {
		AllowedKeys.Add(ObjectKey);

		ObjectToValidate.AllowedTypes = AllowedKeys;
	}
	// Limit the bool to update key selector to accept bools only
	if (BoolKey != nullptr) {
		AllowedKeys.Empty();

		AllowedKeys.Add(BoolKey);

		BoolToUpdate.AllowedTypes = AllowedKeys;
	}
}
// Cache our key data
void UAIE_ValidateObject_BTTaskNode::InitializeFromAsset(UBehaviorTree & Asset) {
	Super::InitializeFromAsset(Asset);
	ObjectToValidate.CacheSelectedKey(Asset.BlackboardAsset);
	BoolToUpdate.CacheSelectedKey(Asset.BlackboardAsset);
}

// Execution
EBTNodeResult::Type UAIE_ValidateObject_BTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	Super::ExecuteTask(OwnerComp, NodeMemory);
	// check we have our blackboard
	if (Blackboard != nullptr) {
		// check the selected keys are valid
		if (Blackboard->IsValidKey(ObjectToValidate.GetSelectedKeyID()) && Blackboard->IsValidKey(BoolToUpdate.GetSelectedKeyID())) {
			// attempt to get the object stored by the key
			UObject* refToObject = Blackboard->GetValue<UBlackboardKeyType_Object>(ObjectToValidate.GetSelectedKeyID());
			// set a bool ref to false if the object is null true if we have an object
			bool boolRef = refToObject == nullptr ? false : true;
			boolRef = bInverseResult ? !boolRef : boolRef;
			// set the update bool
			Blackboard->SetValue<UBlackboardKeyType_Bool>(BoolToUpdate.GetSelectedKeyID(), boolRef);
			// return success
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}