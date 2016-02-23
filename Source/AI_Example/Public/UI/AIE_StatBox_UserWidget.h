// Copyright Jordan Duncan 2016

#pragma once

#include "UI/AIE_Base_UserWidget.h"
#include "AIE_StatBox_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_StatBox_UserWidget : public UAIE_Base_UserWidget
{
	GENERATED_BODY()

public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		TArray<UAIE_Base_UserWidget*> StatBars;

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Construct")
			void BuildWidget();
};
