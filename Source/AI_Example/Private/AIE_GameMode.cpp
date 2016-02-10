// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_GameMode.h"




AAIE_GameMode::AAIE_GameMode()
{
	
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBpClass(*FAIE_Bp_Paths::DefaultPlayerPawnBp);
	if (PlayerPawnBpClass.Class != NULL) {
		DefaultPawnClass = PlayerPawnBpClass.Class;
	}
	// failsafe
	else {
		DefaultPawnClass = AAIE_PlayerPawn::StaticClass();
	}
	// set the default player controller to our blueprinted player controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBpClass(*FAIE_Bp_Paths::PlayerControllerBp);
	if (PlayerControllerBpClass.Class != NULL) {
		PlayerControllerClass = PlayerControllerBpClass.Class;
	}
	// failsafe
	else {
		PlayerControllerClass = AAIE_PlayerController::StaticClass();
	}
	
	//PlayerControllerClass = AAIE_PlayerController::StaticClass();
	//DefaultPawnClass = AAIE_PlayerPawn::StaticClass();
}