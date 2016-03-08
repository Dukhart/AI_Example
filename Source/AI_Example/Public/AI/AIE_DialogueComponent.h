// Copyright Jordan Duncan 2016  

#pragma once

#include "Components/ActorComponent.h"
#include "AIE_DialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AI_EXAMPLE_API UAIE_DialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIE_DialogueComponent();

	// Called when the game starts
	//virtual void BeginPlay() override;
	
	// Called every frame
	//virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gender")
		UDialogueVoice* DialogueVoice;
	
};
