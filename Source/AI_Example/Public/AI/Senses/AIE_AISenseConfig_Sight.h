// Copyright Jordan Duncan 2016

#pragma once

#include "Perception/AISenseConfig_Sight.h"
#include "AIE_AISenseConfig_Sight.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_AISenseConfig_Sight : public UAISenseConfig_Sight
{
	GENERATED_BODY()

public:
		void SetMaxAge(float newMaxAge);
	
};
