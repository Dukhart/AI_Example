// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_IsSelectable.h"


UAIE_IsSelectable::UAIE_IsSelectable(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
// Used to return the content to be displayed on the HUD while object is selected
UAIE_Base_UserWidget* IAIE_IsSelectable::GetSelectedDisplayWidget_Implementation() {
	return nullptr;
}

// Used to tint the colour of the actor while selected
void IAIE_IsSelectable::ActivateSelectionTint_Implementation() {}
// Used to untint the colour of the actor when deselected
void IAIE_IsSelectable::DeactivateSelectionTint_Implementation(){}