// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"
#include "AIE_BotStat_Struct.h"
#include "AIE_ItemStatEffect_Struct.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct AI_EXAMPLE_API FAIE_ItemStatEffect_Struct
{
	GENERATED_USTRUCT_BODY()

		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		EBotStatNames Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatMaxChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatMinChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatDesireChange;

	FAIE_ItemStatEffect_Struct(EBotStatNames InStat = EBotStatNames::SName_None, int32 InStatChange = 0, int32 InStatMaxChange = 0, int32 InStatMinChange = 0, int32 InStatDesireChange = 0) {
		Stat = InStat;
		switch (InStat) {
		case EBotStatNames::SName_Health:
			StatIndex = 0;
			break;
		case EBotStatNames::SName_Stamina:
			StatIndex = 1;
			break;
		case EBotStatNames::SName_Hunger:
			StatIndex = 2;
			break;
		case EBotStatNames::SName_Happiness:
			StatIndex = 3;
			break;

		case EBotStatNames::SName_Strength:
			StatIndex = 0;
			break;
		case EBotStatNames::SName_Intelligence:
			StatIndex = 1;
			break;
		case EBotStatNames::SName_Speed:
			StatIndex = 2;
			break;
		default:
			break;
		}
		StatChange = InStatChange;
		StatMaxChange = InStatMaxChange;
		StatMinChange = InStatMinChange;
		StatDesireChange = InStatDesireChange;
	}
};
