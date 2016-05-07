// Copyright Jordan Duncan 2016

#pragma once

#include "GameFramework/MovementComponent.h"
#include "AIE_AI_MovementComponent.generated.h"


UENUM(BlueprintType)
enum class EMoveProperty : uint8 {
	MaxSpeed UMETA(DisplayName = "Max Speed"),
	Acceleration UMETA(DisplayName = "Acceleration"),
	Gravity UMETA(DisplayName = "Gravity"),
	Mass UMETA(DisplayName = "Mass")
};

UENUM(BlueprintType)
enum class EMoveMode : uint8 {
	Walking UMETA(DisplayName = "Walking"),
	Swimming UMETA(DisplayName = "Swimming"),
	Flying UMETA(DisplayName = "Flying"),
	Jumping UMETA(DisplayName = "Jumping"),

	ALL UMETA(DisplayName = "All")
};
/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_AI_MovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	UAIE_AI_MovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	
};
