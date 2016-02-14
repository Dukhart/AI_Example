// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_Bp_Paths.h"

// player blueprints
const FString FAIE_Bp_Paths::DefaultPlayerPawnBp = FString("APawn'/Game/AI_Example/Blueprints/Player/AIE_PlayerPawn_Bp.AIE_PlayerPawn_Bp_C'");
const FString FAIE_Bp_Paths::PlayerControllerBp = FString("APlayerController'/Game/AI_Example/Blueprints/Player/AIE_PlayerController_Bp.AIE_PlayerController_Bp_C'");

// AI blueprints
const FString FAIE_Bp_Paths::DefaultBotCharacterBp = FString("ACharacter'/Game/AI_Example/Blueprints/AI/AIE_BotCharacter_Bp.AIE_BotCharacter_Bp_C'");
const FString FAIE_Bp_Paths::DefaultBotControllerBp = FString("AAIController'/Game/AI_Example/Blueprints/AI/AIE_AIController_Bp.AIE_AIController_Bp_C'");
const FString FAIE_Bp_Paths::DefaultBotBehaviorTree = FString("BehaviorTree'/Game/AI_Example/Blueprints/AI/AIE_BasicBot_BehaviorTree.AIE_BasicBot_BehaviorTree'");
const FString FAIE_Bp_Paths::DefaultBotBlackboard = FString("BlackboardData'/Game/AI_Example/Blueprints/AI/AIE_BasicBot_BlackboardData.AIE_BasicBot_BlackboardData'");