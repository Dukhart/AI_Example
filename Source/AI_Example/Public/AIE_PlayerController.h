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
	float BaseMovementSpeed = 300.0f;
	// holds delta time
	float DeltaTime = 0.0f;
protected:
	// what happens every frame
	virtual void PlayerTick(float DeltaTime) override;
	// handles what happens when the objet finishes construction
	virtual void BeginPlay() override;
	// handles setting up input, primarly used to bind methods to various inputs
	virtual void SetupInputComponent() override;
	// bools for click detection
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Settings")
	bool bLeftClick = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Settings")
	bool bRightClick = 0;
	// counters for click duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Settings")
	float fClickHoldTime = 0.1f;
	// counters for click duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Settings")
	float fLeftClickCounter = 0.0f;
	// counters for click duration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Settings")
	float fRightClickCounter = 0.0f;

	// input methods
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnMoveLeftRight(float value = 0.0f);
	virtual void OnMoveLeftRight_Implementation(float value = 0.0f);
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnMoveForwardBack(float value = 0.0f);
	virtual void OnMoveForwardBack_Implementation(float value = 0.0f);
	// left mouse button behavior
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnLeftMousePress();
	virtual void OnLeftMousePress_Implementation();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnLeftMouseRelease();
	virtual void OnLeftMouseRelease_Implementation();
	// right mouse button behavior
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnRightMousePress();
	virtual void OnRightMousePress_Implementation();
	UFUNCTION(BlueprintNativeEvent, Category = "Input")
	void OnRightMouseRelease();
	virtual void OnRightMouseRelease_Implementation();

	void DoRightMouseAction(float time);
	void DoLeftMouseAction(float time);

public:
	// Handles execution of valid input
	virtual void DoMoveLeftRight(FVector value);
	virtual void DoMoveForwardBack(FVector value);
	// moves player pawn
	virtual void DoSimpleMove(FVector value);
	void UpdateControlArrow();
};
