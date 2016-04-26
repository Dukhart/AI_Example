// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_Base_UserWidget.h"




void UAIE_Base_UserWidget::SetOwner_Implementation(AActor* NewOwner) {
	if (NewOwner != nullptr) {
		// Set the Owner
		Owner = NewOwner;
		// Rebuild the widget
		//RebuildWidget();
		// update the widget
		UpdateWidget();
	}
}