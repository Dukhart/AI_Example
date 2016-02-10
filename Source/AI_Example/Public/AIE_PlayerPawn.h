// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "AIE_PlayerPawn.generated.h"

UCLASS()
class AI_EXAMPLE_API AAIE_PlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIE_PlayerPawn(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
// Main Pawn components
private:
	// main scene component for the pawn will be used as the root component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	USceneComponent* PawnSceneRoot;
	//USphereComponent* PawnSphere;

	// the main player camera attached to the pawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PawnCamera;
	// the spring arm that will help control the camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* PawnSpringArm;
	// Arrow components for rotation feedback
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* ControlRotationArrow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* PawnRotationArrow;

public:
	// Accessors for Camera Component and Spring arm
	FORCEINLINE class UCameraComponent* GetPawnCamera() const { return PawnCamera; }
	FORCEINLINE class USpringArmComponent* GetPawnSpringArm() const { return PawnSpringArm; }
	// Accessors for Rotation display arrows
	FORCEINLINE class UArrowComponent* GetControlRotationArrow() const { return ControlRotationArrow; }
	FORCEINLINE class UArrowComponent* GetPawnRotationArrow() const { return PawnRotationArrow; }
};
