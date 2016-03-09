// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_StatDesireCheck_BTService.h"


UAIE_StatDesireCheck_BTService::UAIE_StatDesireCheck_BTService(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	NodeName = "Stat Desired BTService";
}
void UAIE_StatDesireCheck_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	EBotStatNames mostDesired = EBotStatNames::SName_None;
	// lowest percent
	float lowestScore = 100;
	if (BotCharacter) {

		// get our characters stats
		TArray<FAIE_BotStat_Struct> stats = BotCharacter->GetStats();
		// refrences to hold stat values for calculation
		float val;
		float min;
		float max;
		float desireMultiplier;
		float percent;
		for (int32 i = 0; i < stats.Num(); ++i) {
			// get current stat values
			val = (float)stats[i].Value;
			min = (float)stats[i].MaxValue;
			max = (float)stats[i].MinValue;
			// get our desire multi and convert to a decimal
			desireMultiplier = stats[i].DesireMultiplier == 0 ? 1 : (float)stats[i].DesireMultiplier;
			desireMultiplier = 1 / desireMultiplier;
			// get percent and apply the multiplier brining the percent down even further if applicable
			if (stats[i].bInverse) {
				percent = (float)stats[i].GetPercent() * desireMultiplier;
				//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Red, " Desire Check " + FString::SanitizeFloat((float)i) + " " + FString::SanitizeFloat(percent));
			}
			else {
				percent = (100.0f - (float)stats[i].GetPercent()) * desireMultiplier;
				//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Red, " Desire Check " + FString::SanitizeFloat((float)i) + " " + FString::SanitizeFloat(percent));
			}
			// if current stats percent score to current lowest score
			if (percent <= statLowValue && percent < lowestScore ) {
				// set the new lowest stat
				mostDesired = stats[i].Stat;
				lowestScore = percent;
			}
		}
	}
	if (Blackboard) {
		FBlackboard::FKey lowStatEnum = Blackboard->GetKeyID("lowStat");
		if (Blackboard->IsValidKey(lowStatEnum)) {
			//if (lowestScore <= statLowValue) {
			//}
			Blackboard->SetValue<UBlackboardKeyType_Enum>(lowStatEnum, static_cast<UBlackboardKeyType_Enum::FDataType>(mostDesired));
		}
	}

}