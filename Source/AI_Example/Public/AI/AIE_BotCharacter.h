// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"

#include "Runtime/UMG/Public/Components/WidgetComponent.h"

#include "AIE_StatBar_UserWidget.h"
#include "AIE_StatBox_UserWidget.h"

#include "AIE_IsUsable.h"
#include "AIE_BotStat_Struct.h"

#include "AIE_BotCharacter.generated.h"

UCLASS()
class AI_EXAMPLE_API AAIE_BotCharacter : public ACharacter, public IAIE_IsUsable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIE_BotCharacter();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// the name of our bot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		FName BotName;
	// COMPONENTS
	// the behavior tree helping control our bots actions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|AI")
		UBehaviorTree* BotBehavior;
	// UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|UI")
		UWidgetComponent* UI_Stat_Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|UI")
		TSubclassOf<UAIE_StatBox_UserWidget> UI_Stat_WidgetTemplate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI")
		UAIE_StatBox_UserWidget* UI_Stat_WidgetInstance;
	

		

	// if set to true native on hit events won't trigger only blueprint version will be called
	UPROPERTY(EditAnywhere, Category = "Hit Detection")
		bool bOverideNativeOnHitEvents = false;
	// if set to true native on take any damage events won't trigger only blueprint version will be called
	UPROPERTY(EditAnywhere, Category = "Hit Detection")
		bool bOverideNativeOnTakeAnyDamage = false;
	// Destroys our Bot
	UFUNCTION(BlueprintCallable, Category = "Actor")
		void Destroy_AIE_Bot();
protected:
	// handles hit detection
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	// handles damage dealt to the bot
	UFUNCTION()
		virtual void AIE_Bot_OnTakeAnyDamage(float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, class AActor* DamageCauser);
	// holds stamina timer data for the TimerManager
	FTimerHandle StaminaTimerHandle;
	// Handles stamina Drain
	void AutoStaminaDrain();

private:
	// array to hold our stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	TArray<FAIE_BotStat_Struct> Stats;
	// array to hold our atributes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
	TArray<FAIE_BotStat_Struct> Attributes;

	// Widget for our stat display
	//UWidgetComponent* StatDisplay;

	/* Removed After Video2
	// our bots health Use Get and Set functions to access
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float Health = 100.0f;
	// our bots stamina Use Get and Set functions to access
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float Stamina = 100.0f;
	*/
public:
	/* Removed After Video2
	// our bots Max health
	UPROPERTY(EditAnywhere, Category = "Stats")
		float MaxHealth = 100.0f;
	// our bots Max Stamina
	UPROPERTY(EditAnywhere, Category = "Stats")
		float MaxStamina = 100.0f;
	*/
	// our bots health regenValue
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Health")
		int32 HealthRegenValue = 1;
	// sets the rate at which stamina will fall, see drain value for how much stamina will fall
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Stamina")
		int32 staminaDrainRate = 1;
	// sets how much the stamina will fall, see Drain Rate for how often stamina will fall
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Stamina")
		int32 staminaDrainValue = 1;
	// the amount of damage a bot will take for having no stamina on health drain
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|Stamina")
		int32 zeroStaminaHealthDrainValue = 5;
public:
	// Get Stat Value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		FAIE_BotStat_Struct GetStat(int32 StatIndex) const;
	// Get Stat Value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatValue(int32 StatIndex) const;
	//Set Stat Value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatValue(int32 newValue, int32 StatIndex);
	// Add inValue to Stat current Value
	UFUNCTION(BlueprintCallable, Category = "Stats")
	void AddStatValue(int32 inValue, int32 StatIndex);
	// Get Stat Max
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatMax(int32 StatIndex) const;
	// Set Stat Max
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatMax(int32 newMax, int32 StatIndex);
	// Get Stat Min
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatMin(int32 StatIndex) const;
	// Set Stat Min
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatMin(int32 newMin, int32 StatIndex);
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatDesire(int32 newDesire, int32 StatIndex);
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatDesire(int32 StatIndex) const;
	/*
	// Get Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		int32 GetHealthValue() const;
	//Set health
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		void SetHealthValue(int32 newHealth);
	// get and set Max Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		int32 GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		void SetMaxHealth(int32 newMaxHealth);
	// Get and Set Min Health
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		int32 GetMinHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Health")
		void SetMinHealth(int32 newMinHealth);

	// Get and Set stamina
	UFUNCTION(BlueprintCallable, Category = "Stats|Stamina")
		int32 GetStaminaValue() const;
	// Set stamina
	UFUNCTION(BlueprintCallable, Category = "Stats|Stamina")
		void SetStaminaValue(int32 newStamina);
	// get and set Max Stamina
	UFUNCTION(BlueprintCallable, Category = "Stats|Stamina")
		int32 GetMaxStamina() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Stamina")
		void SetMaxStamina(int32 newMaxStamina);
	// get and set Min Stamina
	UFUNCTION(BlueprintCallable, Category = "Stats|Stamina")
		int32 GetMinStamina() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Stamina")
		void SetMinStamina(int32 newMinStamina);
	// Get and Set Hunger
	UFUNCTION(BlueprintCallable, Category = "Stats|Hunger")
		int32 GetHungerValue() const;
	// Set stamina
	// stamina can never be below zero stamina will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxStamina is input
	UFUNCTION(BlueprintCallable, Category = "Stats|Hunger")
		void SetHungerValue(int32 newHunger);
	// get and set Max Hunger
	UFUNCTION(BlueprintCallable, Category = "Stats|Hunger")
		int32 GetMaxHunger() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Hunger")
		void SetMaxHunger(int32 newMaxHunger);
	// get and set Min Hunger
	UFUNCTION(BlueprintCallable, Category = "Stats|Hunger")
		int32 GetMinHunger() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Hunger")
		void SetMinHunger(int32 newMinHunger);
	// Get and Set Happiness
	UFUNCTION(BlueprintCallable, Category = "Stats|Happiness")
		int32 GetHappinessValue() const;
	// Set Happiness
	UFUNCTION(BlueprintCallable, Category = "Stats|Happiness")
		void SetHappinessValue(int32 newStamina);
	// get and set Max Happiness
	UFUNCTION(BlueprintCallable, Category = "Stats|Happiness")
		int32 GetMaxHappiness() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Happiness")
		void SetMaxHappiness(int32 newMaxHappiness);
	// get and set Min Happiness
	UFUNCTION(BlueprintCallable, Category = "Stats|Happiness")
		int32 GetMinHappiness() const;
	UFUNCTION(BlueprintCallable, Category = "Stats|Happiness")
		void SetMinHappiness(int32 newMinHappiness);
		*/
	// IsUsable Interface
public:
	void UseItem_Implementation(AAIE_BotCharacter* BotUsing);
	void AI_ActivateUseItem_Implementation(AActor* ActorToUse);

};
