// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_PlantFood_Actor.h"

// constructor
AAIE_PlantFood_Actor::AAIE_PlantFood_Actor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FoodMeshAsset(*FAIE_Asset_Paths::PlantFoodMesh);
	// check if getting the mesh was successfull
	if (FoodMeshAsset.Object) {
		// assign it to the static mesh
		Mesh->SetStaticMesh(FoodMeshAsset.Object);
	}
	Mesh->SetRelativeLocation(FVector(0, 0, -(Mesh->Bounds.SphereRadius / 2)));
	// clear our stats array
	Stats.Empty();
	// set the plants stam restore
	FAIE_ItemStatEffect_Struct stam = FAIE_ItemStatEffect_Struct(EBotStatNames::SName_Stamina, 50);
	Stats.Add(stam);
}

