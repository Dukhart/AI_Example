// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_BaseFoodSpawner.h"


// Sets default values
AAIE_BaseFoodSpawner::AAIE_BaseFoodSpawner(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Comp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshRef(*FAIE_Asset_Paths::TreeMesh);
	if (meshRef.Object) {
		MeshComp->StaticMesh = meshRef.Object;
	}
	// default spawner type
	SpawnerType = ESpawnerType::Radial;
	// default tick rate
	tickRate = 1.0f;
	// default actors per tick
	actorsSpawnedPerTick = 1;
	// sets spawner to loop
	bLoops = true;
	// defaults to infinate
	maxActors = 0;
}
// Called when the game starts or when spawned
void AAIE_BaseFoodSpawner::BeginPlay()
{
	Super::BeginPlay();
	// sets spawner type to assigned spawner type binding the appropriate delegate
	SetSpawnerType(SpawnerType);
	// starts the timer
	// timer won't start if actors spawned is 0 or less
	if (actorsSpawnedPerTick > 0) {
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAIE_BaseFoodSpawner::OnSpawnFood, tickRate, bLoops);
	}
}
// Called every frame
/*
void AAIE_BaseFoodSpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}
*/

void AAIE_BaseFoodSpawner::SetSpawnerType(ESpawnerType newSpawnerType) {
	SpawnFood.Unbind();
	switch (newSpawnerType) {
	case ESpawnerType::Radial:
		SpawnFood.BindUFunction(this, "SpawnFood_Radial");
		break;
	case ESpawnerType::Fountain:
		SpawnFood.BindUFunction(this, "SpawnFood_Fountain");
		break;
	default:
		break;
	}
	SpawnerType = newSpawnerType;
}
ESpawnerType AAIE_BaseFoodSpawner::GetSpawnerType() {
	return SpawnerType;
}
// called by the spawn timer
void AAIE_BaseFoodSpawner::OnSpawnFood() {
	// spawn an actor for every actor spawned per tick
	for (int i = 0; i < actorsSpawnedPerTick; ++i) {
		// if actors hasn't reached max cap spawn an actor
		// or if max cap is infinate spawn an actor
		if (activeActors.Num() <= maxActors || maxActors <= 0) {
			// calls bound spawn method
			SpawnFood.ExecuteIfBound();
		}
	}
}



void AAIE_BaseFoodSpawner::SpawnFood_Radial () {
	//float outerBounds = MeshComp->Bounds.SphereRadius;
	float outerBounds = (MeshComp->Bounds.GetBox().GetSize().Y + MeshComp->Bounds.GetBox().GetSize().X) * 0.3;
	float spawnHeight = MeshComp->Bounds.GetBox().GetSize().Z * 0.75f;


	float randomOffset = FMath::FRandRange(1.0f, 1.5f);
	//float spawnHeight = 400.0f;
	// get random angle
	float angleRadians = FMath::FRandRange(0, 2 * PI);
	// calc x and y cooridanates
	float x = FMath::Sin(angleRadians);
	float y = FMath::Cos(angleRadians);
	// apply cooridinates with offset
	FVector spawnLocation = FVector(x, y, 0.0f) * outerBounds * randomOffset;
	// add the height offset
	spawnLocation.Z = spawnHeight;
	spawnLocation += GetActorLocation();

	FRandomStream randStream;
	randStream.GenerateNewSeed();
	FVector rotV = randStream.VRand();
	FRotator spawnRot = FRotator(rotV.X, rotV.Y, rotV.Z);
	//AAIE_BaseFood_Actor* actorRef = ;

	FVector trace = GetActorLocation();
	trace.Z += spawnHeight;
	// complete line from attemped trace start to end
	DrawDebugLine(GetWorld(), trace, spawnLocation, FColor::Yellow, false, 10);

	// spawn actor
	AAIE_BaseFood_Actor* newActor = GetWorld()->SpawnActor<AAIE_BaseFood_Actor>(FoodToSpawn , spawnLocation, spawnRot);
}
void AAIE_BaseFoodSpawner::SpawnFood_Fountain () {
	FVector spawnLocation = FVector();
	FRotator spawnRot = FRotator();
	//AAIE_BaseFood_Actor* actorRef = ;
	AAIE_BaseFood_Actor* newActor = GetWorld()->SpawnActor<AAIE_BaseFood_Actor>(FoodToSpawn, spawnLocation, spawnRot);
}


void AAIE_BaseFoodSpawner::SetSpawnerValues(float newRate, int32 newActorsSpawnedPerTick, bool bInLoops, int32 newMaxActors){
	maxActors = newMaxActors;
	actorsSpawnedPerTick = newActorsSpawnedPerTick;
	tickRate = newRate;
	bLoops = bInLoops;
	// stops the current timer
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	// timer won't start if actors spawned is 0 or less
	if (newActorsSpawnedPerTick > 0) {
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAIE_BaseFoodSpawner::OnSpawnFood, tickRate, bLoops);
	}
}

float AAIE_BaseFoodSpawner::GetTickRate() {
	return tickRate;
}
bool AAIE_BaseFoodSpawner::GetIsLooping() {
	return bLoops;
}
int32 AAIE_BaseFoodSpawner::GetActorsSpawnedPerTick() {
	return actorsSpawnedPerTick;
}