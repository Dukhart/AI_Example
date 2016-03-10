// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_MostDesiredStat_DP.h"




void UAIE_MostDesiredStat_DP::BindData(UObject* Owner, int32 RequestId) {
	const AAIE_BotCharacter* BotCharacter = Cast<AAIE_BotCharacter>(Owner);
	if (BotCharacter) {
		MostDesiredStatIndex = (uint8)BotCharacter->GetMostDesiredStat();
		//MostDesiredStat = BotCharacter->GetMostDesiredStat();
	}
}