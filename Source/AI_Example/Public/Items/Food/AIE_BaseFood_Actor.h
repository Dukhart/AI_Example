// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "AIE_IsUsable.h"
#include "AIE_ItemStatEffect_Struct.h"

#include "AIE_BaseFood_Actor.generated.h"

UCLASS()
class AI_EXAMPLE_API AAIE_BaseFood_Actor : public AActor, public IAIE_IsUsable
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	AAIE_BaseFood_Actor(const FObjectInitializer& ObjectInitializer);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(VisibleAnywhere, Category = "Actor")
		USceneComponent* SceneComponent;
	// the mesh that will display our food item
	UPROPERTY(EditAnywhere, Category = "Actor")
		UStaticMeshComponent* Mesh;
	//UPROPERTY(EditAnywhere, Category = "Actor")
		//USphereComponent* CollisionSphere;
	// how much health will be restored by picking up this food item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TArray<FAIE_ItemStatEffect_Struct> Stats;


	//UPROPERTY(EditAnywhere, Category = "Stats")
		//float HealthIncreaseValue = 0.0f;
	// how much stamina will be restored by picking up this item
	//UPROPERTY(EditAnywhere, Category = "Stats")
	//	float StaminaIncreaseValue = 5.0f;

	/* // begin ***REMOVED AFTER VIDEO 1*** \\
	// effects whether this food item will automaticly be picked up by anyone who touches it
	UPROPERTY(EditAnywhere, Category = "Function")
	bool bAutoPickup = true;
	// sets blueprints to overide native overlap implementation
	UPROPERTY(EditAnywhere, Category = "Collision")
	bool bOverideNativeOverlapEvents = false;
	// handles overlap events
	UFUNCTION()
	virtual void OnFoodOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	// end ***REMOVED AFTER VIDEO 1*** \\*/

// IsUsable interface functions
public:
	// use item
	void UseItem_Implementation(AAIE_BotCharacter* BotUsing);
	void AI_ActivateUseItem_Implementation(AActor* ActorToUse);
};
