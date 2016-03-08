// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"

#include "AIE_BotStat_Struct.generated.h"

UENUM(BlueprintType)
enum class EBotStatNames : uint8 {
	SName_Health UMETA(DisplayName = "Health"),
	SName_Stamina UMETA(DisplayName = "Stamina"),
	SName_Hunger UMETA(DisplayName = "Hunger"),
	SName_Happiness UMETA(DisplayName = "Happiness"),

	SName_Strength UMETA(DisplayName = "Strength"),
	SName_Intelligence UMETA(DisplayName = "Intelligence"),
	SName_Speed UMETA(DisplayName = "Speed"),

	SName_None UMETA(DisplayName = "None")
};

USTRUCT(BlueprintType)
struct AI_EXAMPLE_API FAIE_StatEffect_Struct
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Effects")
		EBotStatNames Stat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Effects")
		int32 value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Effects")
		int32 takesEffectGreaterThen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Effects")
		int32 takesEffectLessThen;

	FAIE_StatEffect_Struct(EBotStatNames inName = EBotStatNames::SName_None, int32 inValue = 0) {
		Stat = inName;
		value = inValue;

		takesEffectGreaterThen = 101;
		takesEffectLessThen = -1;
	}
};
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
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			EBotStatNames Stat;
	
		// the current value of our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 Value;
		// the Max value of our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 MaxValue;
		// the Minimum value of our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 MinValue;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 DrainRate;
		// the desire multiplier for our stat
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			int32 DesireMultiplier;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
			bool bInverse;
		// stats effected when drained
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Effects")
		TArray<FAIE_StatEffect_Struct> EffectStats;


		// sets default values
	FAIE_BotStat_Struct(EBotStatNames InStat = EBotStatNames::SName_None, int32 inValue = 100, int32 inMax = 100, int32 inMin = 0, int32 inDrainRate = 0, int32 inDesire = 1, bool bInInverse = false) {
		Stat = InStat;
		switch (InStat) {
		case EBotStatNames::SName_Health:
			Name = "Health";
			break;
		case EBotStatNames::SName_Stamina:
			Name = "Stamina";
			break;
		case EBotStatNames::SName_Hunger:
			Name = "Hunger";
			break;
		case EBotStatNames::SName_Happiness:
			Name = "Happiness";
			break;

		case EBotStatNames::SName_Strength:
			Name = "Strength";
			break;
		case EBotStatNames::SName_Intelligence:
			Name = "Intelligence";
			break;
		case EBotStatNames::SName_Speed:
			Name = "Speed";
			break;
		default:
			break;
		}
		Value = inValue;
		MaxValue = inMax;
		MinValue = inMin;
		DrainRate = inDrainRate;
		DesireMultiplier = inDesire;
		bInverse = bInInverse;

		EffectStats = TArray<FAIE_StatEffect_Struct>();
	}

	void SetStatValue(int32 newValue) {
		Value = FMath::Clamp(newValue, MinValue, MaxValue);
	}
	void AddStatValue(int32 addValue) {
		Value = FMath::Clamp(Value + addValue, MinValue, MaxValue);
	}
	int32 GetStatValue() {
		return Value;
	}
	float GetPercent() {
		float percent;

		percent = ((float(Value) - float(MinValue)) / (float(MaxValue) - float(MinValue)) * 100.0f);

		return percent;
	}
};


