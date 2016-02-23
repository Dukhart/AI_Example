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
	// create the ui Component
	UI_Stat_Component = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	// attach our UI to the root
	UI_Stat_Component->AttachTo(RootComponent);
	// set the draw size of our ui
	UI_Stat_Component->SetDrawSize(FVector2D(450.0f, 266.0f));
	
		//BotUI->SetWidget(UIAsset.Object);
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
	FAIE_BotStat_Struct Health("Health");
	// Stamina
	FAIE_BotStat_Struct Stamina("Stamina");
	// Hunger
	FAIE_BotStat_Struct Hunger("Hunger", 0);
	// Happiness
	FAIE_BotStat_Struct Happiness("Happiness", 75, 100, -100);
	// add stats to the array
	Stats.Add(Health);
	Stats.Add(Stamina);
	Stats.Add(Hunger);
	Stats.Add(Happiness);
	// set our bots default attributes
	// Strength
	FAIE_BotStat_Struct Strength("Strength", 10, 25, 1);
	// Intelligence
	FAIE_BotStat_Struct Intelligence("Intelligence", 10, 25, 1);
	// Speed
	FAIE_BotStat_Struct Speed("Speed", 10, 25, 1);
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
	SetStatValue(GetStatMax(0), 0);
	//UIWidgetInstance
	UI_Stat_WidgetInstance = Cast<UAIE_StatBox_UserWidget>(UI_Stat_Component->GetUserWidgetObject());
	if (UI_Stat_WidgetInstance) {
		UI_Stat_WidgetInstance->Owner = this;
		UI_Stat_WidgetInstance->BuildWidget();
		UI_Stat_WidgetInstance->UpdateWidget();
	}
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
	
	// remove incoming damage from total health
	AddStatValue(-FMath::CeilToInt(Damage), 0);
	// check if the bot has died from the incoming damage
	if (GetStatValue(0) <= GetStatMin(0)) {
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
	if (GetStatValue(1) > GetStatMin(1)) {
		// store the stamina before we drain it
		int32 stamRef = GetStatValue(1);
		// set stamRef to the new stamina
		stamRef = stamRef - staminaDrainValue;
		
		// Check if our Bot has run out of stamina
		if (stamRef < GetStatMin(1)) {
			// if it has subtract the min from our new current to get the difference
			// and clamp it to zeroStaminaDrainValue so we don't do more damage then if we already had zero stamina
			int32 stamDamage = FMath::Clamp(stamRef - GetStatMin(1), 0, zeroStaminaHealthDrainValue);
			// TODO:: Make Exhaustion Damage Type
			//UDamageType* DamageType = Cast<UDamageType>(UDamageType::StaticClass());
			// apply the damage to the Bot
			OnTakeAnyDamage.Broadcast(stamDamage, NULL, GetController(), this);
		}
		else { // else stamina stayed above zero so we can allow health regen
			// add the regen value to health
			AddStatValue(HealthRegenValue, 0);
		}
		// set the stamina to our new value
		SetStatValue(stamRef, 1);
	}
	else { // else stamina is already at zero so the Bot will take damage for being over exhausted
	 // apply the damage to the Bot
		OnTakeAnyDamage.Broadcast(zeroStaminaHealthDrainValue, NULL, GetController(), this);
	}
}
// get a stat
FAIE_BotStat_Struct AAIE_BotCharacter::GetStat(int32 StatIndex) const {
	FAIE_BotStat_Struct stat;
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		stat = Stats[StatIndex];
	}
	return stat;
}
// Get Stat Value
int32 AAIE_BotCharacter::GetStatValue(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].Value : NULL;
	return value;
}
//Set Stat Value
void AAIE_BotCharacter::SetStatValue(int32 newValue, int32 StatIndex) {
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		if (newValue < Stats[StatIndex].MinValue) { newValue = Stats[StatIndex].MinValue; }
		else if (newValue > Stats[StatIndex].MaxValue) { newValue = Stats[StatIndex].MaxValue; }
		//FMath::Clamp(newValue, Stats[StatIndex].MinValue, Stats[StatIndex].MaxValue);
		Stats[StatIndex].Value = newValue;
	}
	// update display widget
	if (UI_Stat_WidgetInstance) { UI_Stat_WidgetInstance->UpdateWidget(); }
}
//Add to Stat Value
void AAIE_BotCharacter::AddStatValue(int32 inValue, int32 StatIndex) {
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		inValue = FMath::Clamp(inValue + Stats[StatIndex].Value, Stats[StatIndex].MinValue, Stats[StatIndex].MaxValue);
		Stats[StatIndex].Value = inValue;
	}
	// update display widget
	if (UI_Stat_WidgetInstance) { UI_Stat_WidgetInstance->UpdateWidget(); }
}
// Get Stat Max
int32 AAIE_BotCharacter::GetStatMax(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].MaxValue : NULL;
	return value;
}
// Set Stat Max
void AAIE_BotCharacter::SetStatMax(int32 newMax, int32 StatIndex) {
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		// max can't be lower then the min
		Stats[StatIndex].MaxValue = (newMax < Stats[StatIndex].MinValue) ? Stats[StatIndex].MinValue : newMax;
	}
	// update display widget
	if (UI_Stat_WidgetInstance) { UI_Stat_WidgetInstance->UpdateWidget(); }
}
// Get Stat Min
int32 AAIE_BotCharacter::GetStatMin(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].MinValue : NULL;
	return value;
}
// Set Stat Min
void AAIE_BotCharacter::SetStatMin(int32 newMin, int32 StatIndex) {
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		// min can't be higher then the max
		Stats[StatIndex].MinValue = newMin > Stats[StatIndex].MaxValue ? Stats[StatIndex].MaxValue : newMin;
	}
	// update display widget
	if (UI_Stat_WidgetInstance) { UI_Stat_WidgetInstance->UpdateWidget(); }
}
// set Stat desire
void AAIE_BotCharacter::SetStatDesire(int32 newDesire, int32 StatIndex) {
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		Stats[StatIndex].DesireMultiplier = newDesire;
	}
	// update display widget
	if (UI_Stat_WidgetInstance) { UI_Stat_WidgetInstance->UpdateWidget(); }
}
// get Desire
int32 AAIE_BotCharacter::GetStatDesire(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].DesireMultiplier : NULL;
	return value;
}

// IsUsable interface
void AAIE_BotCharacter::UseItem_Implementation(AAIE_BotCharacter* BotUsing){}

void AAIE_BotCharacter::AI_ActivateUseItem_Implementation(AActor* ActorToUse) {
	// checks we have a valid actor AND that actor implements our IsUsable Interface
	if (ActorToUse && ActorToUse->GetClass()->ImplementsInterface(UAIE_IsUsable::StaticClass())) {
		IAIE_IsUsable::Execute_UseItem(ActorToUse, this);
	}
	else {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " trying to use invalid object IsUsable not Implemented");
#endif
	}
}