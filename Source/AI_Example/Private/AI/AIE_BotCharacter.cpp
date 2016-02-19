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

	// set our bots default stats
	// health
	FAIE_BotStat_Struct Health;
	Health.Name = "Health";
	Health.Value = 100;
	Health.MaxValue = 100;
	Health.MinValue = 0;
	Health.DesireMultiplier = 1;
	// Stamina
	FAIE_BotStat_Struct Stamina;
	Stamina.Name = "Stamina";
	Stamina.Value = 100;
	Stamina.MaxValue = 100;
	Stamina.MinValue = 0;
	Stamina.DesireMultiplier = 1;
	// Hunger
	FAIE_BotStat_Struct Hunger;
	Hunger.Name = "Hunger";
	Hunger.Value = 0;
	Hunger.MaxValue = 100;
	Hunger.MinValue = 0;
	Hunger.DesireMultiplier = 1;
	// Happiness
	FAIE_BotStat_Struct Happiness;
	Happiness.Name = "Happiness";
	Happiness.Value = 75;
	Happiness.MaxValue = 100;
	Happiness.MinValue = -100;
	Happiness.DesireMultiplier = 1;
	// add stats to the array
	Stats.Add(Health);
	Stats.Add(Stamina);
	Stats.Add(Hunger);
	Stats.Add(Happiness);
	// set our bots default attributes
	// Strength
	FAIE_BotStat_Struct Strength;
	Strength.Name = "Happiness";
	Strength.Value = 10;
	Strength.MaxValue = 25;
	Strength.MinValue = 1;
	Strength.DesireMultiplier = 1;
	// Intelligence
	FAIE_BotStat_Struct Intelligence;
	Intelligence.Name = "Intelligence";
	Intelligence.Value = 10;
	Intelligence.MaxValue = 25;
	Intelligence.MinValue = 1;
	Intelligence.DesireMultiplier = 1;
	// Speed
	FAIE_BotStat_Struct Speed;
	Speed.Name = "Speed";
	Speed.Value = 10;
	Speed.MaxValue = 25;
	Speed.MinValue = 1;
	Speed.DesireMultiplier = 1;
	// add atributes to the array
	Attributes.Add(Strength);
	Attributes.Add(Intelligence);
	Attributes.Add(Speed);

}

// Called when the game starts or when spawned
void AAIE_BotCharacter::BeginPlay()
{
	Super::BeginPlay();
	// set our Bots Natural Stamina drain to be triggered by the timer manager
	GetWorldTimerManager().SetTimer(StaminaTimerHandle, this, &AAIE_BotCharacter::AutoStaminaDrain, staminaDrainRate, true);
	// set health to max health
	SetHealthValue(GetMaxHealth());
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
	SetHealthValue(GetHealthValue() - FMath::CeilToInt(Damage));
#if !UE_BUILD_SHIPPING
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " Health " + FString::FromInt(GetHealthValue()));
#endif
	// check if the bot has died from the incoming damage
	if (GetHealthValue() <= 0) {
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
	if (GetStaminaValue() > 0) {
		// store the stamina before we drain it
		int32 stamRef = GetStaminaValue();
		// set stamRef to the new stamina
		stamRef = stamRef - staminaDrainValue;
		// Check if our Bot has run out of stamina
		if (stamRef < 0) {
			// if it has inverse the result with times -1 to get a positive value back
			// and clamp it to zeroStaminaDrainValue so we don't do more damage then if we already had zero stamina
			int32 stamDamage = FMath::Clamp(stamRef * -1, 0, zeroStaminaHealthDrainValue);
			// TODO:: Make Exhaustion Damage Type
			//UDamageType* DamageType = Cast<UDamageType>(UDamageType::StaticClass());
			// apply the damage to the Bot
			OnTakeAnyDamage.Broadcast(stamDamage, NULL, GetController(), this);
		}
		else { // else stamina stayed above zero so we can allow health regen
			// add the regen value to health with set health
			SetHealthValue(GetHealthValue() + HealthRegenValue);
#if !UE_BUILD_SHIPPING
			if (GetHealthValue() < 100.0f) {
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " Health " + FString::FromInt(GetHealthValue()));
			}
#endif
		}
		// set the stamina to our new value
		SetStaminaValue(stamRef);
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, BotName.ToString() + " Stamina " + FString::FromInt(GetStaminaValue()));
#endif
	}
	else { // else stamina is already at zero so the Bot will take damage for being over exhausted
	 // apply the damage to the Bot
		OnTakeAnyDamage.Broadcast(zeroStaminaHealthDrainValue, NULL, GetController(), this);
	}
}
// get health
int32 AAIE_BotCharacter::GetHealthValue() { return Stats[0].Value; }
// set health
// health can never be below zero health will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxHealth is input
void AAIE_BotCharacter::SetHealthValue(int32 newHealth) {
	if (newHealth < 0) { newHealth = 0; }
	else if (newHealth > Stats[0].MaxValue) { newHealth = Stats[0].MaxValue; }
	Stats[0].Value = newHealth;
}
// Get Stamina
int32 AAIE_BotCharacter::GetStaminaValue() { return Stats[1].Value; }
// Set stamina
// stamina can never be below zero stamina will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxStamina is input
void AAIE_BotCharacter::SetStaminaValue(int32 newStamina) {
	if (newStamina < 0) { newStamina = 0; }
	else if (newStamina > Stats[1].MaxValue) { newStamina = Stats[1].MaxValue; }
	Stats[1].Value = newStamina;
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