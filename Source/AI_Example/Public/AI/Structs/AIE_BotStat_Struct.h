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
	FAIE_BotStat_Struct(FName inName = "Stat Name", int32 inValue = 100, int32 inMax = 100, int32 inMin = 0, int32 inDesire = 1) {
		Name = inName;
		Value = inValue;
		MaxValue = inMax;
		MinValue = inMin;
		DesireMultiplier = inDesire;
	}
	
	
	
};
