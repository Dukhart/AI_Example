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

		Mesh->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));
	}
	// clear our stats array
	Stats.Empty();
	// set the plants stam restore
	FAIE_ItemStatEffect_Struct stam = FAIE_ItemStatEffect_Struct(1, 50);
	Stats.Add(stam);
}

