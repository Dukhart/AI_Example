// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/Actor.h"

#include "Components/SphereComponent.h"
#include "AIE_IsUsable.h"
#include "AIE_ItemStatEffect_Struct.h"

#include "AIE_DialogueComponent.h"

// used for perception System
#include "Runtime/AIModule/Classes/Perception/AIPerceptionStimuliSourceComponent.h"
#include "Runtime/AIModule/Classes/Perception/AISense_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionSystem.h"

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
	// extra end play behavior
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// root component of our food item
	//UPROPERTY(VisibleAnywhere, Category = "Actor")
		//USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Actor")
		USphereComponent* rootComp;
	// the mesh that will display our food item
	UPROPERTY(EditAnywhere, Category = "Actor")
		UStaticMeshComponent* Mesh;
	// stimuli component will let the perception system know this component can be seen
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	UAIPerceptionStimuliSourceComponent* StimuliSourceComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Dialogue")
		UAIE_DialogueComponent* DialogueComp;
	// how much health will be restored by picking up this food item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		TArray<FAIE_ItemStatEffect_Struct> Stats;

	class AAIE_BaseFoodSpawner* ownedSpawner;
protected:
	// Forward declaration needed to get around circular dependancy
	// spawner that spawned this food item
	
// IsUsable interface functions
public:
	// use item
	void UseItem_Implementation(AAIE_BotCharacter* BotUsing);
	void AI_ActivateUseItem_Implementation(AActor* ActorToUse);
};
