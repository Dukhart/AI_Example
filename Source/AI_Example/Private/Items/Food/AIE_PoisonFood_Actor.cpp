// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_PoisonFood_Actor.h"



// constructor
AAIE_PoisonFood_Actor::AAIE_PoisonFood_Actor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// get our default plant mesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshObj(*FAIE_Asset_Paths::PoisonFoodMesh);
	if (meshObj.Object) {
		// apply the mesh to our static mesh component
		Mesh->SetStaticMesh(meshObj.Object);

		Mesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	}
	
	// set the poisons stam restore
	StaminaIncreaseValue = 5.0f;
	// set the poisons health damage
	HealthIncreaseValue = -10.0f;
}