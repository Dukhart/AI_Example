// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_PlayerController.h"



// Constructor
AAIE_PlayerController::AAIE_PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	BaseMovementSpeed = 300.0f;
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
	// will auto fire in order so sequence can node from example can be ignored
	// if Left mouse button is down fire left mouse action
	if (bLeftClick) {
		DoLeftMouseAction(DeltaSeconds);
	}
	// if Right mouse button is down fire right mouse action
	if (bRightClick) {
		DoRightMouseAction(DeltaSeconds);
	}
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

	// Bind Input Actions to appropriate Methods
	InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AAIE_PlayerController::OnLeftMousePress);
	InputComponent->BindAction("LeftMouseButton", IE_Released, this, &AAIE_PlayerController::OnLeftMouseRelease);
	InputComponent->BindAction("RightMouseButton", IE_Pressed, this, &AAIE_PlayerController::OnRightMousePress);
	InputComponent->BindAction("RightMouseButton", IE_Released, this, &AAIE_PlayerController::OnRightMouseRelease);
}

// INPUT
// Called when move left right input is detected
void AAIE_PlayerController::OnMoveLeftRight_Implementation(float value) {
#if !UE_BUILD_SHIPPING
	if (value != 0.0f) {
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Red, "Move Left Right " + FString::SanitizeFloat(value) + " at base " + FString::SanitizeFloat(BaseMovementSpeed));
	}
#endif // !UE_BUILD_SHIPPING

	// Get movement Direction based on current control rotation
	FRotator RotationControlSpace = GetControlRotation();
	FVector RightVector = FRotationMatrix(RotationControlSpace).GetUnitAxis(EAxis::Y);
	// multiply movement direction by input value and base speed modifier
	FVector MovementVector = RightVector * value * BaseMovementSpeed;
	// remove any z axis input
	MovementVector = FVector(MovementVector.X, MovementVector.Y, 0.0f);
	// apply the movement to the pawn
	DoMoveLeftRight(MovementVector * DeltaTime);
}
// Called when move forward back input is detected
void AAIE_PlayerController::OnMoveForwardBack_Implementation(float value) {
#if !UE_BUILD_SHIPPING
	if (value != 0.0f) {
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Black, "Move Forward Back " + FString::SanitizeFloat(value) + " at " + FString::SanitizeFloat(BaseMovementSpeed));
	}
#endif  // !UE_BUILD_SHIPPING
	// Get movement Direction based on current control rotation
	FRotator RotationControlSpace = GetControlRotation();
	FVector ForwardVector = FRotationMatrix(RotationControlSpace).GetUnitAxis(EAxis::X);
	// multiply movement direction by input value and base speed modifier
	FVector MovementVector = ForwardVector * value * BaseMovementSpeed;
	// remove any z axis input
	MovementVector = FVector(MovementVector.X, MovementVector.Y, 0.0f);

	// apply the movement to the pawn
	DoMoveForwardBack(MovementVector * DeltaTime);	
}
// Handles execution of valid Left Right input
void AAIE_PlayerController::DoMoveLeftRight(FVector value) {
	DoSimpleMove(value);
}
// Handles execution of valid Forward Back input
void AAIE_PlayerController::DoMoveForwardBack(FVector value) {
	DoSimpleMove(value);
}
// left mouse behavior
void AAIE_PlayerController::OnLeftMousePress_Implementation() {
	bLeftClick = 1;
}
void AAIE_PlayerController::OnLeftMouseRelease_Implementation() {
	if (fLeftClickCounter <= fClickHoldTime) {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Cyan, "Left Mouse Button Clicked");
#endif // !UE_BUILD_SHIPPING
	}
	fLeftClickCounter = 0.0f;
	bLeftClick = 0;
}
void AAIE_PlayerController::DoLeftMouseAction(float time) {
	fLeftClickCounter += time;
	if (fLeftClickCounter > fClickHoldTime) {
		GEngine->AddOnScreenDebugMessage(4, 1.0, FColor::Cyan, "Left Mouse Button Held");
	}
}
// right mouse behavior
void AAIE_PlayerController::OnRightMousePress_Implementation() {
	bRightClick = 1;
}
void AAIE_PlayerController::OnRightMouseRelease_Implementation() {
	if (fRightClickCounter <= fClickHoldTime) {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Cyan, "Right Mouse Button Clicked");
#endif // !UE_BUILD_SHIPPING
	}
	fRightClickCounter = 0.0f;
	bRightClick = 0;
}
void AAIE_PlayerController::DoRightMouseAction(float time) {
	fRightClickCounter += time;
	if (fRightClickCounter > fClickHoldTime) {
		GEngine->AddOnScreenDebugMessage(4, 1.0, FColor::Cyan, "Right Mouse Button Held");
	}
}

//Moves the pawn
void AAIE_PlayerController::DoSimpleMove(FVector value) {
	if (GetPawn() != NULL && value != FVector(0, 0, 0)) {
#if !UE_BUILD_SHIPPING
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Blue, value.ToString());
#endif // !UE_BUILD_SHIPPING
	// move pawn
		GetPawn()->AddActorLocalOffset(value);
	}
	// update controll arrow
	UpdateControlArrow();
}
//updates directional arrow indicators
void AAIE_PlayerController::UpdateControlArrow() {
	if (GetPawn() != NULL) {
		UArrowComponent* ArrowRef = Cast<AAIE_PlayerPawn>(GetPawn())->GetControlRotationArrow();
		check(ArrowRef);
		ArrowRef->SetWorldRotation(GetControlRotation());
	}
}
