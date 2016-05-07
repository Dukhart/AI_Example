// Copyright Jordan Duncan 2016

#include "AI_Example.h"

#include "AIE_BotCharacter.h"
#include "AIE_AIController.h"

#include "AIE_IsUsable.h"

// Constructor
AAIE_BotCharacter::AAIE_BotCharacter(const FObjectInitializer& ObjectInitializer) : Super (ObjectInitializer.SetDefaultSubobjectClass<UAIE_AI_MovementComponent>(ACharacter::CharacterMovementComponentName)) {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// set the default name of the bot
	BotName = "Default Bot";
	// Perception
	sightRange = 500;
	sightLossFalloff = 500;
	sightPeripheralAngle = 90;
	// get our default behavior tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BehaviorTreeAsset(*FAIE_Bp_Paths::DefaultBotBehaviorTree);
	if (BehaviorTreeAsset.Object) {
		// assign the behavior tree to our Bot Behavior
		BotBehavior = BehaviorTreeAsset.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> HealthBTAsset(*FAIE_Asset_Paths::BotHealthBehavior);
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> StaminaBTAsset(*FAIE_Asset_Paths::BotStaminaBehavior);
	if (HealthBTAsset.Object) {
		BotStatBehavior.Add(HealthBTAsset.Object);
	}
	if (StaminaBTAsset.Object) {
		BotStatBehavior.Add(StaminaBTAsset.Object);
	}
	// create the selected ui Component
	UI_Selected_Component = CreateDefaultSubobject<UWidgetComponent>("Selected Widget Component");
	// attach our UI to the root
	UI_Selected_Component->AttachTo(RootComponent);
	// set the draw size of the ui
	//UI_Selected_Component->SetDrawSize(FVector2D(100.0f, 100.0f));
	// set relative location of the ui
	UI_Selected_Component->SetRelativeLocation(FVector(0, 0, 100));

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
		// Get refrence to the mesh's materials
		MainMaterials = GetMesh()->GetMaterials();
		// set selected materials to the same number of elements
		SelectedMaterials.SetNum(MainMaterials.Num());
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
	// rotaton should be based on move direction not controller
	bUseControllerRotationYaw = false;
	// set default AI contoller
	ConstructorHelpers::FClassFinder<AAIController> controlRef(*FAIE_Bp_Paths::DefaultBotControllerBp);
	if (controlRef.Class) {
		AIControllerClass = controlRef.Class;
	}
	else {
		AIControllerClass = AAIE_AIController::StaticClass();
	}
	// set auto possess AI param
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// bind the on take damage delegate to our bots take damage function
	if (!bOverideNativeOnTakeAnyDamage) {
		OnTakeAnyDamage.AddDynamic(this, &AAIE_BotCharacter::AIE_Bot_OnTakeAnyDamage);
	}
	DialogueComp = CreateDefaultSubobject<UAIE_DialogueComponent>("Dialogue Component");
	ConstructorHelpers::FObjectFinder<UDialogueVoice> voiceRef(*FAIE_Asset_Paths::DefaultBotVoice);
	if (voiceRef.Object) {
		DialogueComp->DialogueVoice = voiceRef.Object;
	}
	// set our bots default stats
	// health
	FAIE_BotStat_Struct Health(EBotStatNames::SName_Health);
	// Stamina
	FAIE_BotStat_Struct Stamina(EBotStatNames::SName_Stamina, 100, 100,0, 2);
	FAIE_StatEffect_Struct ref;
	// add health drain when we don't have stam
	ref.Stat = EBotStatNames::SName_Health;
	ref.takesEffectLessThen = 0;
	ref.value = -5;
	Stamina.EffectStats.Add(ref);
	// add health increaxe when we have stam
	ref = FAIE_StatEffect_Struct();
	ref.Stat = EBotStatNames::SName_Health;
	ref.takesEffectGreaterThen = 10;
	ref.value = 5;
	Stamina.EffectStats.Add(ref);
	// Hunger
	FAIE_BotStat_Struct Hunger(EBotStatNames::SName_Hunger, 0, 100, 0, 1, 1, true);
	// Happiness
	FAIE_BotStat_Struct Happiness(EBotStatNames::SName_Happiness, 75, 100, -100, 1);

	

	// add stats to the array
	Stats.Add(Health);
	Stats.Add(Stamina);
	Stats.Add(Hunger);
	Stats.Add(Happiness);
	// set our bots default attributes
	// Strength
	FAIE_BotStat_Struct Strength(EBotStatNames::SName_Strength, 10, 25, 1);
	// Intelligence
	FAIE_BotStat_Struct Intelligence(EBotStatNames::SName_Intelligence, 10, 25, 1);
	// Speed
	FAIE_BotStat_Struct Speed(EBotStatNames::SName_Speed, 10, 25, 1);
	// add atributes to the array
	Stats.Add(Strength);
	Stats.Add(Intelligence);
	Stats.Add(Speed);

}
// Called when the game starts or when spawned
void AAIE_BotCharacter::BeginPlay()
{
	Super::BeginPlay();
	// set our Bots Natural Stamina drain to be triggered by the timer manager
	//GetWorldTimerManager().SetTimer(StaminaTimerHandle, this, &AAIE_BotCharacter::AutoStaminaDrain, staminaDrainRate, true);
	GetWorldTimerManager().SetTimer(StatTimerHandle, this, &AAIE_BotCharacter::AutoStatDrain, AutoDrainRate, true);
	// set health to max health
	SetStatValue(GetStatMax(0), 0);
	//UIWidgetInstance
	UGameInstance* GI = GetGameInstance();
	if (GI) {
		UI_Stat_WidgetInstance = CreateWidget<UAIE_Base_UserWidget>(GI, UI_Stat_WidgetTemplate);
	}
	if (UI_Stat_WidgetInstance != nullptr) {
		UI_Stat_WidgetInstance->Owner = this;
		UI_Stat_WidgetInstance->BuildWidget();
		UI_Stat_WidgetInstance->UpdateWidget();
	}
	// get the insance of the selected display
	UI_SelectedWidgetInstance = Cast<UAIE_Base_UserWidget>(UI_Selected_Component->GetUserWidgetObject());
	if (UI_SelectedWidgetInstance != nullptr) {
		// hide the selected display
		UI_SelectedWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		FLinearColor colRef(UI_SelectedWidgetInstance->ColorAndOpacity);
		colRef.A = 0;
		UI_SelectedWidgetInstance->SetColorAndOpacity(colRef);
	}
	// was on controller possess caused error in editor when trying to open blueprint derived from our AAIE_BotCharacter
	AAIE_AIController* controlRef = Cast<AAIE_AIController>(GetController());
	if (controlRef) {
		// get the black board from the pawn behavior tree
		controlRef->BlackBoardComp->InitializeBlackboard(*(BotBehavior->BlackboardAsset));
		// Get and set starting values of blackboard keys
		FBlackboard::FKey lowStatEnumKey = controlRef->BlackBoardComp->GetKeyID("lowStat");
		if (controlRef->BlackBoardComp->IsValidKey(lowStatEnumKey)) {
			controlRef->BlackBoardComp->SetValue<UBlackboardKeyType_Enum>(lowStatEnumKey, static_cast<UBlackboardKeyType_Enum::FDataType>(EBotStatNames::SName_None));
		}
		// start the behvior tree from the pawn
		controlRef->BehaviorTreeComp->StartTree(*(BotBehavior));
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
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, BotName.ToString() + " Native Hit Detection");
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
		Destroy();
	}
}
// extra destroy behavior
void AAIE_BotCharacter::BeginDestroy() {
	// check that we have a controller
	if (GetController()) {
		// tell the controller to UnPossess the pawn
		GetController()->UnPossess();
	}
	// Remove any timers this bot has active from the manager
	if (GetWorld()) {
		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
		
	}
	// call the super
	Super::BeginDestroy();
}
// handles draining stats automaticly over time
void AAIE_BotCharacter::AutoStatDrain() {
	for (int32 index = 0; index < Stats.Num(); ++index) {
		if (Stats[index].DrainRate != 0) {
			// get the percent of the stat
			float percent = Stats[index].GetPercent();
			if (Stats[index].EffectStats.Num() > 0) {
				for (int32 eIndex = 0; eIndex < Stats[index].EffectStats.Num(); ++eIndex) {
					// check if the current percent is equal to or greater than the greater effect percent
					// or if the current percent is equal to or less than the less effect percent
					if (percent >= Stats[index].EffectStats[eIndex].takesEffectGreaterThen || percent <= Stats[index].EffectStats[eIndex].takesEffectLessThen) {
						// apply stat effect
						if (Stats[index].EffectStats[eIndex].Stat == EBotStatNames::SName_Health && Stats[index].EffectStats[eIndex].value < 0) {
							OnTakeAnyDamage.Broadcast(Stats[index].EffectStats[eIndex].value * -1, NULL, GetController(), this);
						}
						else {
							AddStatValue(Stats[index].EffectStats[eIndex].value, Stats[index].EffectStats[eIndex].Stat);
						}
						
					}
				}
			}
			// drain the stat
			if (Stats[index].bInverse) {
				Stats[index].AddStatValue(Stats[index].DrainRate);
			}
			else {
				Stats[index].AddStatValue(Stats[index].DrainRate * -1);
			}
		}
	}
	// update display widget
	if (UI_Stat_WidgetInstance) { UI_Stat_WidgetInstance->UpdateWidget(); }
}

TArray<FAIE_BotStat_Struct> AAIE_BotCharacter::GetStats() const {
	return Stats;
}
// get a stat
FAIE_BotStat_Struct AAIE_BotCharacter::GetStat(EBotStatNames InName) const {
	FAIE_BotStat_Struct stat = GetStat((uint8)InName);
	
	return stat;
}

FAIE_BotStat_Struct AAIE_BotCharacter::GetStat(int32 StatIndex) const {
	FAIE_BotStat_Struct stat;
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		stat = Stats[StatIndex];
	}
	return stat;
}
// Get Stat Value
int32 AAIE_BotCharacter::GetStatValue(EBotStatNames InName) const {
	int32 val = GetStatValue((uint8)InName);
	return val;
}

int32 AAIE_BotCharacter::GetStatValue(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].Value : NULL;
	return value;
}
//Set Stat Value
void AAIE_BotCharacter::SetStatValue(int32 newValue, EBotStatNames InName) {

	SetStatValue(newValue, (uint8)InName);
}
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
void AAIE_BotCharacter::AddStatValue(int32 inValue, EBotStatNames InName) {
	AddStatValue(inValue, (uint8)InName);
}
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
int32 AAIE_BotCharacter::GetStatMax(EBotStatNames InName) const {
	int32 val = GetStatMax((uint8)InName);
	return val;
}
int32 AAIE_BotCharacter::GetStatMax(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].MaxValue : NULL;
	return value;
}
// Set Stat Max
void AAIE_BotCharacter::SetStatMax(int32 newMax, EBotStatNames InName) {
	SetStatMax(newMax, (uint8)InName);
}
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
int32 AAIE_BotCharacter::GetStatMin(EBotStatNames InName) const {
	int32 val = GetStatMin((uint8)InName);
	return val;
}
int32 AAIE_BotCharacter::GetStatMin(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].MinValue : NULL;
	return value;
}
// Set Stat Min
void AAIE_BotCharacter::SetStatMin(int32 newMin, EBotStatNames InName) {
	SetStatMin(newMin, (uint8)InName);
}
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
void AAIE_BotCharacter::SetStatDesire(int32 newDesire, EBotStatNames InName) {
	SetStatDesire(newDesire, (uint8)InName);
}
void AAIE_BotCharacter::SetStatDesire(int32 newDesire, int32 StatIndex) {
	// check we have a valid index
	if (Stats.IsValidIndex(StatIndex)) {
		Stats[StatIndex].DesireMultiplier = newDesire;
	}
	// update display widget
	if (UI_Stat_WidgetInstance) { UI_Stat_WidgetInstance->UpdateWidget(); }
}
// get Desire
int32 AAIE_BotCharacter::GetStatDesire(EBotStatNames InName) const {
	int32 val = GetStatDesire((uint8)InName);

	return val;
}
int32 AAIE_BotCharacter::GetStatDesire(int32 StatIndex) const {
	// check we have a valid index
	int32 value = Stats.IsValidIndex(StatIndex) ? Stats[StatIndex].DesireMultiplier : NULL;
	return value;
}





// PERCEPTION
void AAIE_BotCharacter::SetSightRange(float newRange) {
	AAIE_AIController* ControlRef = Cast<AAIE_AIController>(GetController());
	if (ControlRef && ControlRef->SightConfig) {
		sightRange = newRange;
		ControlRef->SightConfig->SightRadius = sightRange;
		
		ControlRef->UpdateSenseConfig();
	}
}

void AAIE_BotCharacter::SetSightLossFalloff(float newFalloff) {
	AAIE_AIController* ControlRef = Cast<AAIE_AIController>(GetController());
	if (ControlRef && ControlRef->SightConfig) {
		sightLossFalloff = newFalloff;
		ControlRef->SightConfig->LoseSightRadius = sightRange + sightLossFalloff;

		ControlRef->UpdateSenseConfig();
	}
}

void AAIE_BotCharacter::SetPeripheralVisionAngle(float newAngle) {
	AAIE_AIController* ControlRef = Cast<AAIE_AIController>(GetController());
	if (ControlRef && ControlRef->SightConfig) {
		sightPeripheralAngle = newAngle;
		ControlRef->SightConfig->PeripheralVisionAngleDegrees = sightPeripheralAngle;

		ControlRef->UpdateSenseConfig();
	}
}
float AAIE_BotCharacter::GetSightRange() {
	return sightRange;
}
float AAIE_BotCharacter::GetSightLossFalloff() {
	return sightLossFalloff;
}

float AAIE_BotCharacter::GetPeripheralVisionAngle() {
	return sightPeripheralAngle;
}

// DIALOGUE
void AAIE_BotCharacter::DialogCallout_Implementation(AActor* thingTalkingAbout) {
	// get the game instance
	UAIE_GameInstance* AIE_GI = Cast<UAIE_GameInstance>(GetGameInstance());
	// get a refrence to the dialog component of the actor we are trying to talk about / to
	UAIE_DialogueComponent* thingDialogueCompRef = Cast<UAIE_DialogueComponent>(thingTalkingAbout->GetComponentByClass(UAIE_DialogueComponent::StaticClass()));
	// check we have a game instance and a dialog refrence
	if (thingDialogueCompRef && AIE_GI) {
		// get the voice type of the actor we are trying to talk to / about
		UDialogueVoice* thingVoice = thingDialogueCompRef->DialogueVoice;
		// make a dialogue context with our bot as the speaker and the actor we are trying to talk about / to
		FDialogueContext dContext = FDialogueContext::FDialogueContext();
		dContext.Speaker = DialogueComp->DialogueVoice;
		TArray<UDialogueVoice*> targ;
		targ.AddUnique(thingVoice);
		//dContext.Targets.Add(thingVoice);
		dContext.Targets = targ;

		// look for the wave file that contains our audio
		FStringAssetReference waveRef(*FAIE_Asset_Paths::BotFoundItWave);
		// load the wave
		UDialogueWave* waveToPlay = Cast<UDialogueWave>(AIE_GI->StreamableManager.SynchronousLoad(waveRef));
		// if we found the wave and it supports our context
		if (waveToPlay && waveToPlay->SupportsContext(dContext)) {
			// make the audio component
			UAudioComponent* aud = NewObject<UAudioComponent>(this, "Audio");
			// make sure we made the audio comp
			if (aud) {
				// register the component
				aud->RegisterComponent();
				// attach the component to the bot
				aud->AttachTo(RootComponent);
				aud->SetRelativeLocation(FVector());
				// set the wave based on our context
				aud->SetSound(waveToPlay->GetWaveFromContext(dContext));
				// play the audio
				aud->Play();
				// destroys the component when sound is done playing
				aud->bAutoDestroy = true;
			}
			
		}
	}
}

EBotStatNames AAIE_BotCharacter::GetMostDesiredStat() const {
	EBotStatNames mostDesired = EBotStatNames::SName_None;

	// lowest percent
	float lowestScore = FLT_MAX;

	float desireMultiplier;
	float percent;
	for (int32 i = 0; i < Stats.Num(); ++i) {
		// get our desire multi and convert to a decimal
		desireMultiplier = Stats[i].DesireMultiplier == 0 ? 1 : (float)Stats[i].DesireMultiplier;
		desireMultiplier = 1 / desireMultiplier;
		// get percent and apply the multiplier brining the percent down even further if applicable
		//percent = Stats[i].GetPercent();
		if (Stats[i].bInverse) {
			percent = (100.0f - Stats[i].GetPercent()) * desireMultiplier;
			//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Red, " Desire Check " + FString::SanitizeFloat((float)i) + " " + FString::SanitizeFloat(percent));
		}
		else {
			percent = Stats[i].GetPercent() * desireMultiplier;
			//GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Red, " Desire Check " + FString::SanitizeFloat((float)i) + " " + FString::SanitizeFloat(percent));
		}
		// if current stats percent score to current lowest score
		if (percent <= Stats[i].lowPercent && percent < lowestScore) {
			// set the new lowest stat
			mostDesired = Stats[i].Stat;
			lowestScore = percent;
		}
	}
	return mostDesired;
}

// * INTERFACES * //
// * IsUsable interface
void AAIE_BotCharacter::UseItem_Implementation(AAIE_BotCharacter* BotUsing) {}

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

// * AIAnimation Interface
void AAIE_BotCharacter::TaskToController_Implementation(EMontageNames eAnimName) {

}
void AAIE_BotCharacter::ControllerToCharacter_Implementation(EMontageNames eAnimName) {
	if (GetMesh() && GetMesh()->GetAnimInstance() != NULL && GetMesh()->GetAnimInstance()->Implements<UAIE_AIAnimationInterface>()) {
		IAIE_AIAnimationInterface::Execute_CharacterToAnimBp(GetMesh()->GetAnimInstance(), eAnimName);
	}
}
void AAIE_BotCharacter::CharacterToAnimBp_Implementation(EMontageNames eAnimName) {

}

// * IsSelectable
// Used to return the content to be displayed on the HUD while object is selected
UAIE_Base_UserWidget* AAIE_BotCharacter::GetSelectedDisplayWidget_Implementation() {
	return UI_Stat_WidgetInstance;
}

// Used to tint the colour of the actor while selected
void AAIE_BotCharacter::ActivateSelectionTint_Implementation() {
	if (UI_SelectedWidgetInstance != nullptr) {
		// make the selected widget visible
		UI_SelectedWidgetInstance->SetVisibility(ESlateVisibility::Visible);
		FLinearColor colRef(UI_SelectedWidgetInstance->ColorAndOpacity);
		colRef.A = 1;
		UI_SelectedWidgetInstance->SetColorAndOpacity(colRef);
	}
	// check we can get the mesh
	if (GetMesh() != nullptr) {
		for (int32 index = 0; index < SelectedMaterials.Num(); ++index) {
			// check the index has a valid material
			if (SelectedMaterials[index] != nullptr) {
				// set the material
				GetMesh()->SetMaterial(index, SelectedMaterials[index]);
			}
		}
	}
}
// Used to untint the colour of the actor when deselected
void AAIE_BotCharacter::DeactivateSelectionTint_Implementation() {
	if (UI_SelectedWidgetInstance != nullptr) {
		// hide the selection widget
		UI_SelectedWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		FLinearColor colRef(UI_SelectedWidgetInstance->ColorAndOpacity);
		colRef.A = 0;
		UI_SelectedWidgetInstance->SetColorAndOpacity(colRef);
	}
	// check we can get the mesh
	if (GetMesh() != nullptr) {
		for (int32 index = 0; index < MainMaterials.Num(); ++index) {
			// check the index has a valid material
			if (MainMaterials[index] != nullptr) {
				// set the material
				GetMesh()->SetMaterial(index, MainMaterials[index]);
			}
		}
	}
}