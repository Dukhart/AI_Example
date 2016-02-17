// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_PlantFood_Actor.h"

// constructor
AAIE_PlantFood_Actor::AAIE_PlantFood_Actor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	// get our default plant mesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> meshObj(*FAIE_Asset_Paths::PlantFoodMesh);
	if (meshObj.Object) {
		// apply the mesh to our static mesh component
		Mesh->SetStaticMesh(meshObj.Object);
	}
	// set the plants stam restore
	StaminaIncreaseValue = 50.0f;
}

