// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"

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

	// will call use item on objects that have the IsUsable interface
	//UFUNCTION(BlueprintNativeEvent, Category = "Actions")
	//void UseItemAction(AActor* ActorToUse);
	//virtual void UseItemAction_Implementation(AActor* ActorToUse);

	// the name of our bot
	UPROPERTY(EditAnywhere, Category = "Character")
		FName BotName;
	// the behavior tree helping control our bots actions
	UPROPERTY(EditAnywhere, Category = "AI")
		UBehaviorTree* BotBehavior;

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

	UPROPERTY(VisibleAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FAIE_BotStat_Struct Health;
	UPROPERTY(VisibleAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	FAIE_BotStat_Struct Stamina;


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
	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 HealthRegenValue = 1;
	// sets the rate at which stamina will fall, see drain value for how much stamina will fall
	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 staminaDrainRate = 1;
	// sets how much the stamina will fall, see Drain Rate for how often stamina will fall
	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 staminaDrainValue = 1;
	// the amount of damage a bot will take for having no stamina on health drain
	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 zeroStaminaHealthDrainValue = 5;
public:
	// Get Health
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetHealth();
	//Set health
	// health can never be below zero health will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxHealth is input
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetHealth(int32 newHealth);
	// get and set Max Health
	FORCEINLINE int32 GetMaxHealth() const { return Health.MaxValue; }
	FORCEINLINE void SetMaxHealth(int32 newMaxHealth) { Health.MaxValue = newMaxHealth; }

	// Get and Set stamina
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStamina();
	// Set stamina
	// stamina can never be below zero stamina will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxStamina is input
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStamina(int32 newStamina);
	// get and set Max Stamina
	FORCEINLINE int32 GetMaxStamina() const { return Stamina.MaxValue; }
	FORCEINLINE void SetMaxStamina(int32 newMaxStamina) { Stamina.MaxValue = newMaxStamina; }

	// IsUsable Interface
public:
	void UseItem_Implementation(AAIE_BotCharacter* BotUsing);
	void AI_UseItem_Implementation(AActor* ActorUsing);

};
