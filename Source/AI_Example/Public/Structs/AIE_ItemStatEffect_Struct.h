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

		// Index of the stat updated when SetStat is called to set the stat enum
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		int32 StatIndex;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
		EBotStatNames Stat;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatMaxChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatMinChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatDesireChange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
		bool bIsInverse;

	FAIE_ItemStatEffect_Struct(EBotStatNames InStat = EBotStatNames::SName_None, int32 InStatChange = 0, int32 InStatMaxChange = 0, int32 InStatMinChange = 0, int32 InStatDesireChange = 0) {
		Stat = InStat;
		bIsInverse = false;

		StatIndex = (uint8)InStat;

		StatChange = InStatChange;
		StatMaxChange = InStatMaxChange;
		StatMinChange = InStatMinChange;
		StatDesireChange = InStatDesireChange;
	}

		inline void SetStat(EBotStatNames InStat = EBotStatNames::SName_None){
		Stat = InStat;
		StatIndex = (uint8)InStat;
	}
};
