// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_PlayerPawn.h"


// Sets default values
AAIE_PlayerPawn::AAIE_PlayerPawn (const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//ROOT
	//make the root component
	PawnSceneRoot = CreateDefaultSubobject<USceneComponent>("Root Component");
	RootComponent = PawnSceneRoot;

	//SPRING ARM
	// create the spring arm
	PawnSpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	// attach the spring arm to the Root
	PawnSpringArm->AttachTo(RootComponent);
	// set default arm length
	PawnSpringArm->TargetArmLength = 200.0f;
	// set spring arm angle
	//PawnSpringArm->SetRelativeRotation(FQuat(FRotator(20.0f, 0.0f, 0.0f)));

	// CAMERA
	// create the camera
	PawnCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	// attach the camera to the END of the spring arm
	PawnCamera->AttachTo(PawnSpringArm, USpringArmComponent::SocketName);

	// DISPLAY ARROWS
	//create arrow to display pawn roation
	PawnRotationArrow = CreateDefaultSubobject<UArrowComponent>("Arrow Pawn Rotation");
	// attach the arrow to the root
	PawnRotationArrow->AttachTo(RootComponent);
	//set unique color for the arrow
	PawnRotationArrow->ArrowColor = FColor::Red;
	// set the arrow to display in game
	PawnRotationArrow->bHiddenInGame = false;

	ControlRotationArrow = CreateDefaultSubobject<UArrowComponent>("Arrow Control Rotation");
	// attach the arrow to the root
	ControlRotationArrow->AttachTo(RootComponent);
	//set unique color for the arrow
	ControlRotationArrow->ArrowColor = FColor::Blue;
	// set the arrow to display in game
	ControlRotationArrow->bHiddenInGame = false;
	// add vertical offset so the arrows are not on top of eachother
	ControlRotationArrow->AddLocalOffset(FVector(0.0f,0.0f,30.0f));
	
}

// Called when the game starts or when spawned
void AAIE_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIE_PlayerPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAIE_PlayerPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

