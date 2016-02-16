// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIE_Bp_Paths.generated.h"
/**
 * 
 */
USTRUCT()
struct AI_EXAMPLE_API FAIE_Bp_Paths
{
	GENERATED_USTRUCT_BODY()
public:
	// Player Blueprints
	static const FString DefaultPlayerPawnBp;
	static const FString PlayerControllerBp;

	// AI Blueprints
	static const FString DefaultBotCharacterBp;
	static const FString DefaultBotControllerBp;
	static const FString DefaultBotBehaviorTree;
	static const FString DefaultBotBlackboard;
};
