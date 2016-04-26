// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"

#include "AIE_Base_UserWidget.h"

#include "AIE_IsSelectable.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class AI_EXAMPLE_API UAIE_IsSelectable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IAIE_IsSelectable {
	GENERATED_IINTERFACE_BODY()

public:
	// Used to return the content to be displayed on the HUD while object is selected
	UFUNCTION(BlueprintNativeEvent, Category = "Selection")
	class UAIE_Base_UserWidget* GetSelectedDisplayWidget();

	// Used to tint the colour of the actor while selected
	UFUNCTION(BlueprintNativeEvent, Category = "Selection")
		void ActivateSelectionTint();
	// Used to untint the colour of the actor when deselected
	UFUNCTION(BlueprintNativeEvent, Category = "Selection")
		void DeactivateSelectionTint();

};
