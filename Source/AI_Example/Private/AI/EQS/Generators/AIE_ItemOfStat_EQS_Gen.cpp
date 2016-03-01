// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_ItemOfStat_EQS_Gen.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

#include "AIE_BaseFood_Actor.h"
#include "AIE_BotCharacter.h"
#include "AIE_AIController.h"


#define LOCTEXT_NAMESPACE "EnvQueryGenerator"

UAIE_ItemOfStat_EQS_Gen::UAIE_ItemOfStat_EQS_Gen(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer) {
	SearchedActorClass = AActor::StaticClass();
	SearchRadius.DefaultValue = 500.0f;
	SearchCenter = UEnvQueryItemType_Actor::StaticClass();
	ItemType = UEnvQueryItemType_Actor::StaticClass();

}
void UAIE_ItemOfStat_EQS_Gen::GenerateItems(FEnvQueryInstance& QueryInstance) const {
	int32 StatIndex;
	switch (StatName) {
	case EBotStatNames::SName_Health:
		StatIndex = 0;
		break;
	case EBotStatNames::SName_Stamina:
		StatIndex = 1;
		break;
	case EBotStatNames::SName_Hunger:
		StatIndex = 2;
		break;
	case EBotStatNames::SName_Happiness:
		StatIndex = 3;
		break;
	case EBotStatNames::SName_Strength:
		StatIndex = 4;
		break;
	case EBotStatNames::SName_Intelligence:
		StatIndex = 5;
		break;
	case EBotStatNames::SName_Speed:
		StatIndex = 6;
		break;
	default:
		StatIndex = -1;
		break;
	}
	// add our owner to the search rad data
	SearchRadius.BindData(QueryInstance.Owner.Get(), QueryInstance.QueryID);
	// get the world
	UWorld* World = GEngine->GetWorldFromContextObject(QueryInstance.Owner.Get());
	if (World == NULL || SearchedActorClass == NULL)
	{
		return;
	}

	//float RadiusValue = SearchRadius.GetValue();
	//const float RadiusSq = FMath::Square(RadiusValue);

	TArray<FVector> ContextLocations;
	QueryInstance.PrepareContext(SearchCenter, ContextLocations);


	AAIE_BotCharacter* ownerRef = Cast<AAIE_BotCharacter>(QueryInstance.Owner.Get());

	if (ownerRef) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, QueryInstance.Owner->GetName() + " getting items of stat");
		AAIE_AIController* controlRef = Cast<AAIE_AIController>(ownerRef->GetController());
		if (controlRef) {
			TArray<AActor*> percievedActors;
			controlRef->GetPerceptionComponent()->GetPerceivedActors(UAISenseConfig_Sight::StaticClass(), percievedActors);
			for (int aIndex = 0; aIndex < percievedActors.Num(); ++aIndex)
			{
				AAIE_BaseFood_Actor* actorRef = Cast<AAIE_BaseFood_Actor>(percievedActors[aIndex]);

				if (actorRef) {
					// get all context locations to compare actors too
					//for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ++ContextIndex)
					//{
						// Check that the actor modifies the searched stat
						for (int32 statIndex = 0; statIndex < actorRef->Stats.Num(); statIndex++) {
							if (actorRef->Stats[statIndex].StatIndex == StatIndex) {
								// make sure the stat has a positive effect
								if (actorRef->Stats[statIndex].StatChange > 0 && !actorRef->Stats[statIndex].bIsInverse) {
									QueryInstance.AddItemData<UEnvQueryItemType_Actor>(actorRef);
								}
								else if (actorRef->Stats[statIndex].StatChange < 0 && actorRef->Stats[statIndex].bIsInverse) {
									QueryInstance.AddItemData<UEnvQueryItemType_Actor>(actorRef);
								}
								break;
							}
						}
					//}
				}
			}

		}
	}
	// get all actors of searched class
	/*
	for (TActorIterator<AActor> ActorItr(World, SearchedActorClass); ActorItr; ++ActorItr) {
		AAIE_BaseFood_Actor* actorRef = Cast<AAIE_BaseFood_Actor>(*ActorItr);

		if (actorRef) {
			// get all context locations to compare actors too
			for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ++ContextIndex)
			{

				// filter out actors out of range
				if (FVector::DistSquared(ContextLocations[ContextIndex], actorRef->GetActorLocation()) < RadiusSq)
				{
					// Check that the actor modifies the searched stat
					for (int32 statIndex = 0; statIndex < actorRef->Stats.Num(); statIndex++) {
						if (actorRef->Stats[statIndex].StatIndex == StatIndex) {
							// make sure the stat has a positive effect
							if (actorRef->Stats[statIndex].StatChange > 0 && !actorRef->Stats[statIndex].bIsInverse) {
								QueryInstance.AddItemData<UEnvQueryItemType_Actor>(actorRef);
							}
							else if (actorRef->Stats[statIndex].StatChange < 0 && actorRef->Stats[statIndex].bIsInverse) {
								QueryInstance.AddItemData<UEnvQueryItemType_Actor>(actorRef);
							}
							break;
						}
					}

				}
			}
		}

	}
	*/
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

