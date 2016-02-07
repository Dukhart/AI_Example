// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_GameMode.h"




AAIE_GameMode::AAIE_GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBpClass(TEXT(""));
	if (PlayerPawnBpClass.Class != NULL) {

	}
	// failsafe
	else {
		DefaultPawnClass = AAIE_PlayerPawn::StaticClass();
	}
	// set the default player controller to our blueprinted player controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBpClass(TEXT(""));
	if (PlayerControllerBpClass.Class != NULL) {

	}
	// failsafe
	else {
		PlayerControllerClass = AAIE_PlayerController::StaticClass();
	}
	/*
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
	DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	*/
}