// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"

#include "AIE_BotCharacter.generated.h"

UCLASS()
class AI_EXAMPLE_API AAIE_BotCharacter : public ACharacter
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
protected:
	// our bots health Use Get and Set functions to access
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float Health = 100.0f;
	// our bots Max health
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float MaxHealth = 100.0f;
	// our bots health regenValue
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float HealthRegenValue = 1.0f;
	// our bots stamina Use Get and Set functions to access
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float Stamina = 100.0f;
	// our bots Max Stamina
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float MaxStamina = 100.0f;
	// sets the rate at which stamina will fall, see drain value for how much stamina will fall
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float staminaDrainRate = 1.0f;
	// sets how much the stamina will fall, see Drain Rate for how often stamina will fall
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float staminaDrainValue = 1.0f;
	// the amount of damage a bot will take for having no stamina on health drain
	UPROPERTY(EditAnywhere, Category = "Stats", meta = (AllowPrivateAccess = "true"))
		float zeroStaminaHealthDrainValue = 5.0f;
	// holds stamina timer data for the TimerManager
	FTimerHandle StaminaTimerHandle;
	// Handles stamina Drain
	void AutoStaminaDrain();
public:
	// Get and Set Health
	FORCEINLINE float GetHealth() const { return Health; }
	// health can never be below zero health will auto correct to zero if a number lower than zero is input and to Max if a number higher then MaxHealth is input
	FORCEINLINE void SetHealth(float newHealth) {
		if (newHealth < 0) { newHealth = 0; }
		else if (newHealth > MaxHealth) { newHealth = MaxHealth; }
		Health = newHealth;
	}

	// Get and Set stamina
	FORCEINLINE float GetStamina() const { return Stamina; }
	// stamina can never be below zero stamina will auto correct to zero if a number lower than zero is input
	FORCEINLINE void SetStamina(float newStamina) {
		if (newStamina < 0) { newStamina = 0; }
		else if (newStamina > MaxStamina) { newStamina = MaxStamina; }
		Stamina = newStamina;
	}
};
