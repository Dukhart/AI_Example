// Copyright Jordan Duncan 2016

#pragma once

#include "EnvironmentQuery/EnvQueryGenerator.h"

#include "AIE_BotStat_Struct.h"

#include "AIE_ItemOfStat_EQS_Gen.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_ItemOfStat_EQS_Gen : public UEnvQueryGenerator
{
	GENERATED_BODY()
		// constructor
		UAIE_ItemOfStat_EQS_Gen(const FObjectInitializer &ObjectInitializer);

	UPROPERTY(EditDefaultsOnly, Category = Generator)
		TSubclassOf<AActor> SearchedActorClass;
	UPROPERTY(EditDefaultsOnly, Category = Generator)
		FAIDataProviderFloatValue SearchRadius;

	UPROPERTY(EditDefaultsOnly, Category = Generator)
		EBotStatNames StatName;
	/** context */
	UPROPERTY(EditAnywhere, Category = Generator)
		TSubclassOf<UEnvQueryContext> SearchCenter;


	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;
	virtual FText GetDescriptionDetails() const override;
	
	
};
