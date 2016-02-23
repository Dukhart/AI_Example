// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"
#include "AIE_IsUsable.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class AI_EXAMPLE_API UAIE_IsUsable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
	
};

class IAIE_IsUsable { 
	GENERATED_IINTERFACE_BODY()

public:
	//UFUNCTION(BlueprintImplementableEvent, Category = "Actions")
		//void UseItem();
	
		UFUNCTION(BlueprintNativeEvent, Category = "Actions")
		void UseItem(AAIE_BotCharacter* BotUsing);
		UFUNCTION(BlueprintNativeEvent, Category = "Actions")
		void AI_ActivateUseItem(AActor* ActorToUse);
		
};
