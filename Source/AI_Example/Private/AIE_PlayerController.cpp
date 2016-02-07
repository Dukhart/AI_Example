// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_PlayerController.h"



// Constructor
AAIE_PlayerController::AAIE_PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
}
// handles what happens when the objet finishes construction
void AAIE_PlayerController::BeginPlay() {
	Super::BeginPlay();
}
// Called every frame
void AAIE_PlayerController::PlayerTick(float DeltaSeconds) {
	Super::PlayerTick(DeltaSeconds);
	fDeltaTime = DeltaSeconds;
}
// handles setting up input, primarly used to bind methods to various inputs
void AAIE_PlayerController::SetupInputComponent() {
	// make the input component from the base class
	Super::SetupInputComponent();
	// check creating the input component was succefull
	// won't execute check if (DO_CHECK=1) is turned off or 0
	check(InputComponent);
	// Bind Input Axis to appropriate Methods
	InputComponent->BindAxis("MoveLeftRight", this, &AAIE_PlayerController::OnMoveLeftRight);
	InputComponent->BindAxis("MoveForwardBack", this, &AAIE_PlayerController::OnMoveForwardBack);
}
// INPUT
// Called when move left right input is detected
void AAIE_PlayerController::OnMoveLeftRight(float value) {
	
	// Get movement Direction based on current control rotation
	FRotator RotationControlSpace = GetControlRotation();
	FVector RightVector = FRotationMatrix(RotationControlSpace).GetUnitAxis(EAxis::X);
	// multiply movement direction by input value and base speed modifier
	FVector MovementVector = RightVector * value * baseMovementSpeed;
	// apply the movement to the pawn
	DoMoveLeftRight(MovementVector * fDeltaTime);
	

}
// Called when move forward back input is detected
void AAIE_PlayerController::OnMoveForwardBack(float value) {
	// Get movement Direction based on current control rotation
	FRotator RotationControlSpace = GetControlRotation();
	FVector ForwardVector = FRotationMatrix(RotationControlSpace).GetUnitAxis(EAxis::Y);
	// multiply movement direction by input value and base speed modifier
	FVector MovementVector = ForwardVector * value * baseMovementSpeed;
	// remove any z axis input
	MovementVector = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	// apply the movement to the pawn
	DoMoveForwardBack(MovementVector * fDeltaTime);
	
	/*
	GetPawn()->AddActorLocalOffset(MovementVector * fDeltaTime);
	//GetPawn()->AddActorLocalOffset(MovementVector);
	*/
}

// Handles execution of valid input
void AAIE_PlayerController::DoMoveLeftRight(FVector value) {
	DoSimpleMove(value);
}
void AAIE_PlayerController::DoMoveForwardBack(FVector value) {
	DoSimpleMove(value);
}
//Moves the pawn and updates direction arrow indicators
void AAIE_PlayerController::DoSimpleMove(FVector value) {
	// move pawn
	GetPawn()->AddActorLocalOffset(value);
	// TODO:: update arrows
}