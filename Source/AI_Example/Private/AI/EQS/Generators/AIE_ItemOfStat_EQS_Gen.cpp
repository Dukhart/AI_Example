// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_ItemOfStat_EQS_Gen.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

#include "AIE_BaseFood_Actor.h"

#define LOCTEXT_NAMESPACE "EnvQueryGenerator"

UAIE_ItemOfStat_EQS_Gen::UAIE_ItemOfStat_EQS_Gen(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
	SearchedActorClass = AActor::StaticClass();
	SearchRadius.DefaultValue = 500.0f;
	SearchCenter = UEnvQueryItemType_Actor::StaticClass();
	ItemType = UEnvQueryItemType_Actor::StaticClass();
}
void UAIE_ItemOfStat_EQS_Gen::GenerateItems(FEnvQueryInstance& QueryInstance) const {
	// add our owner to the search rad data
	SearchRadius.BindData(QueryInstance.Owner.Get(), QueryInstance.QueryID);
	// get the world
	UWorld* World = GEngine->GetWorldFromContextObject(QueryInstance.Owner.Get());
	if (World == NULL || SearchedActorClass == NULL)
	{
		return;
	}
	
	float RadiusValue = SearchRadius.GetValue();
	const float RadiusSq = FMath::Square(RadiusValue);

	TArray<FVector> ContextLocations;
	QueryInstance.PrepareContext(SearchCenter, ContextLocations);
	
	// get all actors of searched class
	for (TActorIterator<AActor> ActorItr(World, SearchedActorClass); ActorItr; ++ActorItr) {
		AAIE_BaseFood_Actor* actorRef = Cast<AAIE_BaseFood_Actor>(*ActorItr);
		
		if (actorRef) {
			// get all context locations to compare actors too
			for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ++ContextIndex)
			{
				
				// filter out actors out of range
				if (FVector::DistSquared(ContextLocations[ContextIndex], actorRef->GetActorLocation()) < RadiusSq)
				{
					// Check for the searched stat
					for (int32 statIndex = 0; statIndex < actorRef->Stats.Num(); statIndex++) {
						if (actorRef->Stats[statIndex].StatIndex == StatIndex) {
							QueryInstance.AddItemData<UEnvQueryItemType_Actor>(actorRef);
							break;
						}
					}

				}
			}
		}
		
	}

}

FText UAIE_ItemOfStat_EQS_Gen::GetDescriptionTitle() const {
	FFormatNamedArguments Args;
	Args.Add(TEXT("DescriptionTitle"), Super::GetDescriptionTitle());
	Args.Add(TEXT("ActorsClass"), FText::FromString(GetNameSafe(SearchedActorClass)));
	Args.Add(TEXT("DescribeContext"), UEnvQueryTypes::DescribeContext(SearchCenter));

	return FText::Format(LOCTEXT("DescriptionGenerateActorsAroundContext", "{DescriptionTitle}: generate set of actors of {ActorsClass} around {DescribeContext}"), Args);
}
FText UAIE_ItemOfStat_EQS_Gen::GetDescriptionDetails() const {
	FFormatNamedArguments Args;
	Args.Add(TEXT("Radius"), FText::FromString(SearchRadius.ToString()));

	FText Desc = FText::Format(LOCTEXT("ActorsOfClassDescription", "radius: {Radius}"), Args);

	return Desc;
}

