// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_PlayerController.h"



// Constructor
AAIE_PlayerController::AAIE_PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	BaseMovementSpeed = 10.0f;
	DeltaTime = 0.0f;
}
// handles what happens when the objet finishes construction
void AAIE_PlayerController::BeginPlay() {
	Super::BeginPlay();
}
// Called every frame
void AAIE_PlayerController::PlayerTick(float DeltaSeconds) {
	Super::PlayerTick(DeltaSeconds);
	DeltaTime = DeltaSeconds;
	
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

//#if UE_BUILD_DEBUG
	if (value != 0.0f) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Move Left Right " + FString::SanitizeFloat(value) + " at " + FString::SanitizeFloat(BaseMovementSpeed));
	}
//#endif

	// Get movement Direction based on current control rotation
	FRotator RotationControlSpace = GetControlRotation();
	FVector RightVector = FRotationMatrix(RotationControlSpace).GetUnitAxis(EAxis::Y);
	// multiply movement direction by input value and base speed modifier
	FVector MovementVector = RightVector * value * BaseMovementSpeed;

	// apply the movement to the pawn
	//DoMoveLeftRight(MovementVector * fDeltaTime);
	DoMoveLeftRight(MovementVector);
}
// Called when move forward back input is detected
void AAIE_PlayerController::OnMoveForwardBack(float value) {
//#if UE_BUILD_DEBUG
	if (value != 0.0f) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Black, "Move Forward Back " + FString::SanitizeFloat(value) + " at " + FString::SanitizeFloat(BaseMovementSpeed));
	}
//#endif
	// Get movement Direction based on current control rotation
	FRotator RotationControlSpace = GetControlRotation();
	FVector ForwardVector = FRotationMatrix(RotationControlSpace).GetUnitAxis(EAxis::X);
	// multiply movement direction by input value and base speed modifier
	FVector MovementVector = ForwardVector * value * BaseMovementSpeed;

	//GetPawn()->AddMovementInput(ForwardVector, value * baseMovementSpeed);

	// remove any z axis input
	//MovementVector = FVector(MovementVector.X, MovementVector.Y, 0.0f);


	// apply the movement to the pawn
	//DoMoveForwardBack(MovementVector * fDeltaTime);
	DoMoveForwardBack(MovementVector);
	


	
	//GetPawn()->AddActorLocalOffset(MovementVector * fDeltaTime);
	//GetPawn()->AddActorLocalOffset(MovementVector);
	
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
	if (GetPawn() != NULL && value != FVector(0, 0, 0)) {
//#if UE_BUILD_DEBUG
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, value.ToString());
//#endif
	// move pawn
	//GetPawn()->AddActorWorldOffset(value);
	
		GetPawn()->AddActorLocalOffset(value);
	}
	// TODO:: update arrows
}
