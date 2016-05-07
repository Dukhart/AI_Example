// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/Actor.h"

#include "AIE_BaseFood_Actor.h"

#include "AIE_BaseFoodSpawner.generated.h"

DECLARE_DELEGATE(FSpawnFood);

UENUM(BlueprintType)
enum class ESpawnerType : uint8 {
	Radial UMETA(DisplayName = "Radial"),
	Fountain UMETA(DisplayName = "Fountain")
};

UENUM(BlueprintType)
enum class ESpawnOrder : uint8 {
	Random,
	Sequence
};

UCLASS()
class AI_EXAMPLE_API AAIE_BaseFoodSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIE_BaseFoodSpawner(const FObjectInitializer& ObjectInitializer);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	// probably wont need tick for this actor
	//virtual void Tick( float DeltaSeconds ) override;
	// the mesh of our spawner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditDefaultsOnly, Category = "Perception")
	UAIPerceptionStimuliSourceComponent* StimuliSourceComp;

	//TSubclassOf<AAIE_BaseFood_Actor> FoodToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		TArray<TSubclassOf<AAIE_BaseFood_Actor>> FoodToSpawn;
	// tells the spawner to keep spawning every tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
		bool bLoops;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Fountain")
		float fountainForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Fountain")
		float upForceMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Fountain")
		float upMinForceMultiplier;

	UPROPERTY()
		TArray<AAIE_BaseFood_Actor*> activeActors;
	void RemoveActiveActor(AAIE_BaseFood_Actor* removeActor);

private:
	// timerhandle for spawn
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
protected:
	// holds spawner type
	// use get set functions to change
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Stats", meta = (AllowPrivateAccess = "true"))
		ESpawnerType SpawnerType;
	// number of acrots to spawn per tick
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Stats", meta = (ClampMin = "0", AllowPrivateAccess = "true"))
		int32 actorsSpawnedPerTick;
	// Ticks before the spawn order will make a new selection
	// 0 will result in never changing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Stats", meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int32 NumberTicksBeforeSelection;
	int32 CurrentTickIndex;
	// if more then one food type can be spawned will effect how food is selected
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Stats", meta = (AllowPrivateAccess = "true"))
	ESpawnOrder SpawnOrder;
	// how often to spawn actors
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawner|Stats", meta = (ClampMin = "0", AllowPrivateAccess = "true"))
		float tickRate;
	// max number of spawned actors
	// 0 or less will be infinate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Stats", meta = (ClampMin = "0", AllowPrivateAccess = "true"))
		int32 maxActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Stats", meta = (ClampMin = "0", AllowPrivateAccess = "true"))
	int32 CurrentSpawnIndex;


	FSpawnFood SpawnFood;
	// sets spawner type
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void SetSpawnerType(ESpawnerType newSpawnerType);
	UFUNCTION(BlueprintCallable, Category = "Spawner")
		ESpawnerType GetSpawnerType();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
		void GetNextSelection();

	// spawns food based on assigned value of the spawnFood delegate
	UFUNCTION()
		void OnSpawnFood();
	// spawns food radial style
	UFUNCTION()
	void SpawnFood_Radial();
	// spawns food fountain style
	UFUNCTION()
	void SpawnFood_Fountain();

	// set spawner values
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SetSpawnerValues(float newRate = 1.0f, int32 newActorsSpawnedPerTick = 1, bool bInLoops = true, int32 newMaxActors = 0);
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	float GetTickRate();
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	bool GetIsLooping();
	UFUNCTION(BlueprintCallable, Category = "Spawner")
	int32 GetActorsSpawnedPerTick();

};
