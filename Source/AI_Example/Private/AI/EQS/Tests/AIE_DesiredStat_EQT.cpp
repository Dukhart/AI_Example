// Copyright Jordan Duncan 2016

#include "AI_Example.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "AIE_BaseFood_Actor.h"

#include "AIE_DesiredStat_EQT.h"




UAIE_DesiredStat_EQT::UAIE_DesiredStat_EQT(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_Actor::StaticClass();

	FloatValueMax.DefaultValue = 100.0f;
	FloatValueMin.DefaultValue = 0.0f;
}
void UAIE_DesiredStat_EQT::RunTest(FEnvQueryInstance& QueryInstance) const {
	// get the owner
	UObject* Owner = QueryInstance.Owner.Get();
	// if we don't have a valid owner return
	if (Owner == nullptr) {
		return;
	}
	// max stat value
	FloatValueMax.BindData(Owner, QueryInstance.QueryID);
	const float MaxStatValue = FloatValueMax.GetValue();
	// min stat value
	FloatValueMin.BindData(Owner, QueryInstance.QueryID);
	const float MinStatValue = FloatValueMin.GetValue();
	// the stat index we are looking for
	StatIndex.BindData(Owner, QueryInstance.QueryID);
	const uint8 NeededStat = StatIndex.GetValue();

	// get the items from the generator
	for (FEnvQueryInstance::ItemIterator Item(this, QueryInstance); Item; ++Item) {
		// get our food item
		const AAIE_BaseFood_Actor* FoodActor = Cast<AAIE_BaseFood_Actor>(GetItemActor(QueryInstance, Item.GetIndex()));
		// get our stat enum as a UEnum
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EBotStatNames"), true);
		// check if we have a valid enum value
		if (enumPtr && enumPtr->IsValidEnumValue(NeededStat)) {
			// cast the value to the enum
			EBotStatNames name = static_cast<EBotStatNames>(NeededStat);
			// get the amount the actor effects the stat
			const float ItemScore = FoodActor ? FoodActor->GetStatEffectByName(name) : 0;
			// set the score
			Item.SetScore(TestPurpose, FilterType, ItemScore, MinStatValue, MaxStatValue);
		}
		


	}

}
FText UAIE_DesiredStat_EQT::GetDescriptionTitle() const {
	return FText::FromString(TEXT("Amount of Stat Restored"));
}