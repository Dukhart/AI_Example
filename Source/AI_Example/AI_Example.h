// Copyright Jordan Duncan 2016

#pragma once

#include "Engine.h"

// Global Classes
#include "AIE_PlayerPawn.h"
#include "AIE_PlayerController.h"

#include "AIE_GameInstance.h"

// strings
#include "AIE_Bp_Paths.h"
#include "AIE_Asset_Paths.h"

//General Log
DECLARE_LOG_CATEGORY_EXTERN(GeneralLog, Log, All);
//General debug Log
DECLARE_LOG_CATEGORY_EXTERN(DebugLog, Log, All);
//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(InitLog, Log, All);
//Logging for your AI system
DECLARE_LOG_CATEGORY_EXTERN(AILog, Log, All);
//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(CriticalErrorsLog, Log, All);