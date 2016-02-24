// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|AI")
		TArray<UBehaviorTree*> BotStatBehavior;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|AI")
		// BotBehavior;
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
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", meta = (AllowPrivateAccess = "true"))
		//TArray<FAIE_BotStat_Struct> Attributes;
public:

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
	// Get all stats
	UFUNCTION(BlueprintCallable, Category = "Stats")
		TArray<FAIE_BotStat_Struct> GetStats() const;
	// Get Stat
	UFUNCTION(BlueprintCallable, Category = "Stats")
		FAIE_BotStat_Struct GetStat(EBotStatNames InName) const;
	FAIE_BotStat_Struct GetStat(int32 StatIndex) const;
	// Get Stat Value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatValue(EBotStatNames InName) const;
	int32 GetStatValue(int32 StatIndex) const;
	//Set Stat Value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatValue(int32 newValue, EBotStatNames InName);
	void SetStatValue(int32 newValue, int32 StatIndex);
	// Add inValue to Stat current Value
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void AddStatValue(int32 inValue, EBotStatNames InName);
	void AddStatValue(int32 inValue, int32 StatIndex);
	// Get Stat Max
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatMax(EBotStatNames InName) const;
	int32 GetStatMax(int32 StatIndex) const;
	// Set Stat Max
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatMax(int32 newMax, EBotStatNames InName);
	void SetStatMax(int32 newMax, int32 StatIndex);
	// Get Stat Min
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatMin(EBotStatNames InName) const;
	int32 GetStatMin(int32 StatIndex) const;
	// Set Stat Min
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatMin(int32 newMin, EBotStatNames InName);
	void SetStatMin(int32 newMin, int32 StatIndex);
	UFUNCTION(BlueprintCallable, Category = "Stats")
		void SetStatDesire(int32 newDesire, EBotStatNames InName);
	void SetStatDesire(int32 newDesire, int32 StatIndex);
	UFUNCTION(BlueprintCallable, Category = "Stats")
		int32 GetStatDesire(EBotStatNames InName) const;
	int32 GetStatDesire(int32 StatIndex) const;
	// IsUsable Interface
public:
	void UseItem_Implementation(AAIE_BotCharacter* BotUsing);
	void AI_ActivateUseItem_Implementation(AActor* ActorToUse);

};
