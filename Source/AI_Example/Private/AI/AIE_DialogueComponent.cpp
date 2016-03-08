// Copyright Jordan Duncan 2016  

#include "AI_Example.h"
#include "AIE_DialogueComponent.h"


// Sets default values for this component's properties
UAIE_DialogueComponent::UAIE_DialogueComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = false;
	PrimaryComponentTick.bCanEverTick = false;

	// set dialog gender
	ConstructorHelpers::FObjectFinder<UDialogueVoice> voiceRef(*FAIE_Asset_Paths::DefaultDialogVoice);
		if (voiceRef.Object) {
			DialogueVoice = voiceRef.Object;
		}
}

/*
// Called when the game starts
void UAIE_DialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIE_DialogueComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}
*/

