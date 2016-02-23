// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"
#include "AIE_ItemStatEffect_Struct.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct AI_EXAMPLE_API FAIE_ItemStatEffect_Struct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatMaxChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatMinChange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int32 StatDesireChange;

	FAIE_ItemStatEffect_Struct(int32 InStatIndex = 0, int32 InStatChange = 0, int32 InStatMaxChange = 0, int32 InStatMinChange = 0, int32 InStatDesireChange = 0) {
			StatIndex = InStatIndex;

			StatChange = InStatChange;
			StatMaxChange = InStatMaxChange;
			StatMinChange = InStatMinChange;
			StatDesireChange = InStatDesireChange;
	}
};
