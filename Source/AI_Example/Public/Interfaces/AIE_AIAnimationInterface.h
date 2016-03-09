// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"
#include "AIE_AIAnimationInterface.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EMontageNames : uint8 {
	Eat UMETA(DisplayName = "Eat"),

	None UMETA(DisplayName = "None")
};

UINTERFACE(Blueprintable)
class AI_EXAMPLE_API UAIE_AIAnimationInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IAIE_AIAnimationInterface {
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void TaskToController(EMontageNames eAnimName);
	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void ControllerToCharacter(EMontageNames eAnimName);
	UFUNCTION(BlueprintNativeEvent, Category = "Animation")
	void CharacterToAnimBp(EMontageNames eAnimName);
};