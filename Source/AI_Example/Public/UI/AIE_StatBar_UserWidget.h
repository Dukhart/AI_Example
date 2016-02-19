// Copyright Jordan Duncan 2016

#pragma once

#include "UI/AIE_Base_UserWidget.h"

#include "AIE_BotStat_Struct.h"

#include "AIE_StatBar_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_StatBar_UserWidget : public UAIE_Base_UserWidget
{
	GENERATED_BODY()

public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		FAIE_BotStat_Struct StatData;
	
};
