// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_BaseFood_Actor.h"

#include "AIE_BotCharacter.h"
#include "AIE_BaseFoodSpawner.h"



// Sets default values
AAIE_BaseFood_Actor::AAIE_BaseFood_Actor(const FObjectInitializer& ObjectInitializer) 
	: Super (ObjectInitializer) {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// create the root component
	//SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Root");
	// make scene component the root component
	//RootComponent = SceneComponent;
	rootComp = CreateDefaultSubobject<USphereComponent>("Scene Root");
	RootComponent = rootComp;
	rootComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	rootComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	rootComp->SetSimulatePhysics(true);
	rootComp->SetSphereRadius(5.0f);
	// make the static mesh component
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	// attach the mesh to the root
	Mesh->AttachTo(RootComponent);
	
	//RootComponent = Mesh;
	// get our default mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FoodMeshAsset(*FAIE_Asset_Paths::DefaultFoodMesh);
	// check if getting the mesh was successfull
	if (FoodMeshAsset.Object) {
		// assign it to the static mesh
		Mesh->SetStaticMesh(FoodMeshAsset.Object);
	}
	StimuliSourceComp = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSource");
	//StimuliSourceComp->
	DialogueComp = CreateDefaultSubobject<UAIE_DialogueComponent>("Dialogue Component");
	FAIE_ItemStatEffect_Struct stam = FAIE_ItemStatEffect_Struct(EBotStatNames::SName_Stamina, 5);
	Stats.Add(stam);
}

// Called when the game starts or when spawned
void AAIE_BaseFood_Actor::BeginPlay()
{
	Super::BeginPlay();

	
	Mesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Mesh->SetSimulatePhysics(true);
	Mesh->SetRelativeLocation(FVector(0, 0, -(Mesh->Bounds.SphereRadius / 2)));
	Mesh->WeldTo(RootComponent);

	StimuliSourceComp->RegisterForSense(UAISense_Sight::StaticClass());

	//UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, UAISense_Sight::StaticClass(), this);

}

// Called every frame
void AAIE_BaseFood_Actor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
// IsUsable interface functions
// use item
void AAIE_BaseFood_Actor::UseItem_Implementation(AAIE_BotCharacter* BotUsing) {
	// check we have a valid bot
	if (BotUsing) {
#if !UE_BUILD_SHIPPING
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, " Food Hit by " + BotUsing->BotName.ToString());
#endif
		for (int32 i = 0; i < Stats.Num(); i++) {
			int32 s = Stats[i].StatIndex;
			// check if we are affecting health as negative health values need to be handled as damage
			if (s == 0 && Stats[i].StatChange < 0) {
				// apply health damage
				BotUsing->OnTakeAnyDamage.Broadcast(Stats[i].StatChange * -1.0f, NULL, NULL, this);
			}
			// change stat
			else { BotUsing->AddStatValue(Stats[i].StatChange, s); }
			// apply stat affects to Max
			BotUsing->SetStatMax(BotUsing->GetStatMax(s) + Stats[i].StatMaxChange, s);
			// apply stat affects to Min
			BotUsing->SetStatMin(BotUsing->GetStatMin(s) + Stats[i].StatMinChange, s);
			// apply stat affects to Desire
			BotUsing->SetStatDesire(BotUsing->GetStatDesire(s) + Stats[i].StatDesireChange, s);
		}
		
		// Destroy the food item as it has been consumed
		Destroy();
		GetWorld()->ForceGarbageCollection(true);
	}
}
void AAIE_BaseFood_Actor::AI_ActivateUseItem_Implementation(AActor* ActorToUse) {
}
// extra end play behavior
void AAIE_BaseFood_Actor::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	if (ownedSpawner) {
		ownedSpawner->RemoveActiveActor(this);
	}
	Super::EndPlay(EndPlayReason);
}

int32 AAIE_BaseFood_Actor::GetStatEffectByName(EBotStatNames inName) const {
	int32 effectVal = NULL;
	// iterate through the stats this item effects
	for (int32 statIndex = 0; statIndex < Stats.Num(); ++statIndex) {
		// when we find one that matches the searched name
		if (Stats[statIndex].Stat == inName) {
			// put the amount it effects the stat in the effect val
			effectVal = Stats[statIndex].StatChange;
			// break out of the loop as we have found what we are looking for
			break;
		}
	}
	return effectVal;
}