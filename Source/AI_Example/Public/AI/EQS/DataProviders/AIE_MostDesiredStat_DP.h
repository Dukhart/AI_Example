// Copyright Jordan Duncan 2016

#pragma once

#include "DataProviders/AIDataProvider_QueryParams.h"


#include "AIE_BotCharacter.h"

#include "AIE_MostDesiredStat_DP.generated.h"

/**
 * 
 */
UCLASS(EditInlineNew, meta = (DisplayName = "Owner\'s properties"))
class AI_EXAMPLE_API UAIE_MostDesiredStat_DP : public UAIDataProvider_QueryParams
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
		int32 MostDesiredStatIndex;
	//UPROPERTY()
		//EBotStatNames MostDesiredStat;

	virtual void BindData(UObject* Owner, int32 RequestId) override;
};
