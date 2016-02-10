// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "AIE_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API AAIE_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	// class setup
public:
	// handles what happens when the controller is first created
	AAIE_PlayerController(const FObjectInitializer& ObjectInitializer);
	// the base movement speed modifier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseMovementSpeed;
	// holds delta time
	float DeltaTime;
protected:
	// what happens every frame
	virtual void PlayerTick(float DeltaTime) override;
	// handles what happens when the objet finishes construction
	virtual void BeginPlay() override;
	// handles setting up input, primarly used to bind methods to various inputs
	
	virtual void SetupInputComponent() override;
	// input methods
public:
	
	// called when input is detected
	virtual void OnMoveLeftRight(float value = 0.0f);
	virtual void OnMoveForwardBack(float value = 0.0f);
	
	// Handles execution of valid input
	virtual void DoMoveLeftRight(FVector value);
	virtual void DoMoveForwardBack(FVector value);
	// moves player pawn
	virtual void DoSimpleMove(FVector value);
	
};
