// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"
#include "AIE_BotStat_Struct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AI_EXAMPLE_API FAIE_BotStat_Struct
{
	GENERATED_USTRUCT_BODY()
		// the name of our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			FName Name;
		// the current value of our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 Value;
		// the Max value of our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 MaxValue;
		// the Minimum value of our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 MinValue;
		// the desire multiplier for our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 DesireMultiplier;


		// sets default values
	FAIE_BotStat_Struct() {
		Name = "Stat Name";
		Value = 100;
		MaxValue = 100;
		MinValue = 0;
		DesireMultiplier = 1;
	}
	
	
	
};
