// Copyright Jordan Duncan 2016

#pragma once

#include "EnvironmentQuery/EnvQueryTest.h"
#include "AIE_DesiredStat_EQT.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_DesiredStat_EQT : public UEnvQueryTest
{
	GENERATED_BODY()
	
protected:
	// gets the desired stat from the data provider
	UPROPERTY(EditDefaultsOnly, Category = "Test")
	FAIDataProviderIntValue StatIndex;

	UAIE_DesiredStat_EQT(const FObjectInitializer& ObjectIntitializer = FObjectInitializer::Get());
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	virtual FText GetDescriptionTitle() const override;

};
