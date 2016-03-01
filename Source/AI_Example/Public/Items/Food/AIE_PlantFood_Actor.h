// Copyright Jordan Duncan 2016

#pragma once

#include "Items/Food/AIE_BaseGoodFood_Actor.h"
#include "AIE_PlantFood_Actor.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API AAIE_PlantFood_Actor : public AAIE_BaseGoodFood_Actor
{
	GENERATED_BODY()
	
public:
	// constructor
	AAIE_PlantFood_Actor(const FObjectInitializer& ObjectInitializer);


};
