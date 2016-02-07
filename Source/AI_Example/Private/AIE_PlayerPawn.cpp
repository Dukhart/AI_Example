// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Example.h"
#include "AIE_PlayerPawn.h"


// Sets default values
AAIE_PlayerPawn::AAIE_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create arrow to display control rotation
	//UArrowComponent* arrowControlRot = new UArrowComponent();
	UArrowComponent* arrowControlRot = CreateDefaultSubobject<UArrowComponent>("Arrow Control Rotation");
	// attach the arrow to the root
	arrowControlRot->AttachTo(RootComponent);
	//set unique color for the arrow
	arrowControlRot->ArrowColor = FColor::Blue;

	//create arrow to display camera roation
	UArrowComponent* arrowCameraRot = CreateDefaultSubobject<UArrowComponent>("Arrow Camera Rotation");
	// attach the arrow to the root
	arrowCameraRot->AttachTo(RootComponent);
	//set unique color for the arrow
	arrowCameraRot->ArrowColor = FColor::Red;
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

