// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/PlayerController.h"

// includes for HUD classes
#include "AIE_Base_UserWidget.h"

#include "AIE_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API AAIE_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// * MOVEMENT SETTINGS * //
	// the base movement speed modifier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float BaseMovementSpeed = 300.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseCameraSpeed = 1.0f;
	// holds delta time
	float DeltaTime = 0.0f;
protected:
	

	// * INITIALIZATION * //
	// handles what happens when the controller is first created
	AAIE_PlayerController(const FObjectInitializer& ObjectInitializer);
	// handles what happens when the objet finishes construction
	virtual void BeginPlay() override;
	// handles setting up input, primarly used to bind methods to various inputs
	virtual void SetupInputComponent() override;
	// * HUD * //
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	//	TSubclassOf<UAIE_StatBox_UserWidget> BotStatDisplayTemplate;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
	//	UAIE_StatBox_UserWidget* BotStatDisplayInstance;

	// * TICK & TIMERS * //
	// what happens every frame
	virtual void PlayerTick(float DeltaTime) override;

	// * INPUT * //
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
	UFUNCTION()
	void DoRightMouseAction(float time);
	UFUNCTION()
	void DoLeftMouseAction(float time);
	// what happens when right mouse is click is detected
	UFUNCTION()
		void DoRightMouseClick();
	// what happens when left mouse is click is detected
	UFUNCTION()
		void DoLeftMouseClick();

	// * ACTOR SELECT * //
	// Ref to our selected actor if any
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Selection")
		AActor* SelectedActor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
		UAIE_Base_UserWidget* SelectedActorWidgetInstance;
	// selects an actor for HUD feedback
	UFUNCTION(BlueprintCallable, Category = "Selection")
		void SelectActor(AActor* NewSelection);
	// remove selected actor
	UFUNCTION(BlueprintCallable, Category = "Selection")
		void DeselectActor();

public:
	// * MOVENENT * //
	// Handles execution of valid input
	virtual void DoMoveLeftRight(FVector value);
	virtual void DoMoveForwardBack(FVector value);
	// moves player pawn
	virtual void DoSimpleMove(FVector value);
	void UpdateControlArrow();
};
