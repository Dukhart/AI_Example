// Copyright Jordan Duncan 2016

#pragma once
#include "AIE_Asset_Paths.generated.h"
/**
 * 
 */
USTRUCT()
struct AI_EXAMPLE_API FAIE_Asset_Paths
{
	GENERATED_USTRUCT_BODY()
public:
	// bot assets
	// base Bot
	static const FString DefaultBotMesh;
	static const FString DefaultBotAnim;
	static const FString DefaultBotUI;
	// Items
	//Food
	static const FString DefaultFoodMesh;
	static const FString PlantFoodMesh;
	static const FString PoisonFoodMesh;
};