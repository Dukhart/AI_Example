// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_BotCharacter.h"

#include "AIE_AIController.h"

// Sets default values
AAIE_BotCharacter::AAIE_BotCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// get our default behavior tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAsset(*FAIE_Bp_Paths::DefaultBotBehaviorTree);
	if (BehaviorTreeAsset.Object) {
		// assign the behavior tree to our Bot Behavior
		BotBehavior = BehaviorTreeAsset.Object;
	}
	// get the refrence to our skeletal mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshObj(*FAIE_Asset_Paths::DefaultBotMesh);
	// check that we got the mesh and a mesh component exists
	if (MeshObj.Object && GetMesh() != NULL) {
		// assign the mesh to the mesh component
		GetMesh()->SetSkeletalMesh(MeshObj.Object);
		// set the starting location and rotation for the mesh
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -85.0f), FRotator(0.0f, -90.0f, 0.0f));
		// get a refrence to our default animations
		static ConstructorHelpers::FObjectFinder<UAnimBlueprintGeneratedClass> AnimRef(*FAIE_Asset_Paths::DefaultBotAnim);
		if (AnimRef.Object) {
			// set the character mesh to use our animation blueprint
			GetMesh()->AnimBlueprintGeneratedClass = AnimRef.Object;
		}
		// set default movement speeds
		CharacterMovement->MaxWalkSpeed = 400.0f;
		CharacterMovement->MaxWalkSpeedCrouched = 200.0f;
		// set default AI contoller
		AIControllerClass = AAIE_AIController::StaticClass();
		// set auto possess AI param
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
	



}

// Called when the game starts or when spawned
void AAIE_BotCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAIE_BotCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAIE_BotCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

