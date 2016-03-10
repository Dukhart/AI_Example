// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_MostDesiredStat_DP.h"




void UAIE_MostDesiredStat_DP::BindData(UObject* Owner, int32 RequestId) {
	const AAIE_BotCharacter* BotCharacter = Cast<AAIE_BotCharacter>(Owner);
	if (BotCharacter) {

		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EBotStatNames"), true);
		if (enumPtr == nullptr) {
			return;
		}
		int32 maxIndex = enumPtr->NumEnums();
		int32 desiredIndex = (uint8)BotCharacter->GetMostDesiredStat();
		MostDesiredStatIndex = FMath::Clamp(desiredIndex , 0, maxIndex);
		//MostDesiredStat = BotCharacter->GetMostDesiredStat();
	}
}