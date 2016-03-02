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
		Mesh->SetSimulatePhysics(true);
	}
	// clear our stats array
	Stats.Empty();
	// set the poisons stam restore
	FAIE_ItemStatEffect_Struct stam = FAIE_ItemStatEffect_Struct(EBotStatNames::SName_Stamina, 5);
	// set the poisons health damage
	FAIE_ItemStatEffect_Struct hp = FAIE_ItemStatEffect_Struct(EBotStatNames::SName_Health, -15);
	// add stat effects to the array
	Stats.Add(stam);
	Stats.Add(hp);
}