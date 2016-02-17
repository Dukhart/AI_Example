// Copyright Jordan Duncan 2016

#include "AI_Example.h"

#include "AIE_BotCharacter.h"
#include "AIE_AIController.h"

#include "AIE_IsUsable.h"

// Constructor
AAIE_BotCharacter::AAIE_BotCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set the default name of the bot
	BotName = "Default Bot";
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
	}
	// set default movement speeds
	if (GetCharacterMovement()) {
		GetCharacterMovement()->MaxWalkSpeed = 400.0f;
		GetCharacterMovement()->MaxWalkSpeedCrouched = 200.0f;
		GetCharacterMovement()->RotationRate.Yaw = 160.0f;
		GetCharacterMovement()->MaxAcceleration = 600.0f;
		// rotaton should be based on move direction
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
#if !UE_BUILD_SHIPPING
	else {
		UE_LOG(DebugLog, Error, TEXT("AIE_BotCharacter Missing Movement Component"));
	}
#endif // !UE_BUILD_SHIPPING
	// rotaton should be based on move direction not controller
	bUseControllerRotationYaw = false;
	// set default AI contoller
	AIControllerClass = AAIE_AIController::StaticClass();
	// set auto possess AI param
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// bind the on take damage delegate to our bots take damage function
	if (!bOverideNativeOnTakeAnyDamage) {
		OnTakeAnyDamage.AddDynamic(this, &AAIE_BotCharacter::AIE_Bot_OnTakeAnyDamage);
	}
}

// Called when the game starts or when spawned
void AAIE_BotCharacter::BeginPlay()
{
	Super::BeginPlay();
	// set our Bots Natural Stamina drain to be triggered by the timer manager
	GetWorldTimerManager().SetTimer(StaminaTimerHandle, this, &AAIE_BotCharacter::AutoStaminaDrain, staminaDrainRate, true);
	// set health to max health
	SetHealth(GetMaxHealth());
}

// Called every frame
void AAIE_BotCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIE_BotCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}
/*
// calls use item on an item
void AAIE_BotCharacter::UseItemAction_Implementation(AActor* ActorToUse) {
	// checks we have a valid actor AND that actor implements our IsUsable Interface
	if (ActorToUse && GetClass()->ImplementsInterface(UAIE_IsUsable::StaticClass())) {
		IAIE_IsUsable::Execute_UseItem(ActorToUse, this);
	}
	else {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " trying to use invalid object IsUsable not Implemented");
#endif
	}
	
}
*/
// handles Hit detection
void AAIE_BotCharacter::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) {
	// won't fire our native hit event if blueprints set the overide bool to true
	if (bOverideNativeOnHitEvents == false) {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " Native Hit Detection");
#endif
	}
	/*	super will call blueprint implementation See AActor implementation of NotifyHit
	 *	not tied to the bOverideNativeOnHitEvents bool so blueprints can add on to native functionality or override completely
	*/
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
}

// handles damage Input 
// won't be bound if bOverideNativeOnTakeAnyDamage is set to true
void AAIE_BotCharacter::AIE_Bot_OnTakeAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser) {
	// remove incoming damage from total health and set health 
	SetHealth(GetHealth() - Damage);
#if !UE_BUILD_SHIPPING
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " Health " + FString::SanitizeFloat(Health));
#endif
	// check if the bot has died from the incoming damage
	if (GetHealth() <= 0) {
		// destroys the bot
		Destroy_AIE_Bot();
	}
}

// Handles Destroying the Bot
void AAIE_BotCharacter::Destroy_AIE_Bot() {
	// check that we have a controller
	if (GetController()) {
		// tell the controller to UnPossess the pawn
		GetController()->UnPossess();
	}
	// Remove any timers this bot has active from the manager
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	// Destroy this Actor
	Destroy();
}

// Handles Natural Stamina Drain
void AAIE_BotCharacter::AutoStaminaDrain() {
	// we might make a Damage type later use this for now as take any damage must have a damage type input
	// if stamina is currently greater then zero drian stamina
	if (GetStamina() > 0) {
		// store the stamina before we drain it
		float stamRef = GetStamina();
		// set stamRef to the new stamina
		stamRef = stamRef - staminaDrainValue;
		// Check if our Bot has run out of stamina
		if (stamRef < 0) {
			// if it has inverse the result with times -1 to get a positive value back
			// and clamp it to zeroStaminaDrainValue so we don't do more damage then if we already had zero stamina
			float stamDamage = FMath::Clamp(stamRef * -1.0f, 0.0f, zeroStaminaHealthDrainValue);
			// TODO:: Make Exhaustion Damage Type
			//UDamageType* DamageType = Cast<UDamageType>(UDamageType::StaticClass());
			// apply the damage to the Bot
			OnTakeAnyDamage.Broadcast(stamDamage, NULL, GetController(), this);
		}
		else { // else stamina stayed above zero so we can allow health regen
			// add the regen value to health with set health
			SetHealth(GetHealth() + HealthRegenValue);
#if !UE_BUILD_SHIPPING
			if (GetHealth() < 100.0f) {
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " Health " + FString::SanitizeFloat(Health));
			}
#endif
		}
		// set the stamina to our new value
		SetStamina(stamRef);
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, BotName.ToString() + " Stamina " + FString::SanitizeFloat(Stamina));
#endif
	}
	else { // else stamina is already at zero so the Bot will take damage for being over exhausted
	 // apply the damage to the Bot
		OnTakeAnyDamage.Broadcast(zeroStaminaHealthDrainValue, NULL, GetController(), this);
	}
}
// get health
float AAIE_BotCharacter::GetHealth() { return Health; }
// set health
// health can never be below zero health will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxHealth is input
void AAIE_BotCharacter::SetHealth(float newHealth) {
	if (newHealth < 0) { newHealth = 0; }
	else if (newHealth > MaxHealth) { newHealth = MaxHealth; }
	Health = newHealth;
}
// Get Stamina
float AAIE_BotCharacter::GetStamina() { return Stamina; }
// Set stamina
// stamina can never be below zero stamina will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxStamina is input
void AAIE_BotCharacter::SetStamina(float newStamina) {
	if (newStamina < 0) { newStamina = 0; }
	else if (newStamina > MaxStamina) { newStamina = MaxStamina; }
	Stamina = newStamina;
}

// IsUsable interface
void AAIE_BotCharacter::UseItem_Implementation(AAIE_BotCharacter* BotUsing){}

void AAIE_BotCharacter::AI_UseItem_Implementation(AActor* ActorUsing){
	// checks we have a valid actor AND that actor implements our IsUsable Interface
	if (ActorUsing && ActorUsing->GetClass()->ImplementsInterface(UAIE_IsUsable::StaticClass())) {
		IAIE_IsUsable::Execute_UseItem(ActorUsing, this);
	}
	else {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " trying to use invalid object IsUsable not Implemented");
#endif
	}
}