// Copyright Jordan Duncan 2016

#pragma once

#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"

#include "AIE_Base_UserWidget.generated.h"

/**
 *
 */
UCLASS()
class AI_EXAMPLE_API UAIE_Base_UserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
		AActor* Owner;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Update")
		void UpdateWidget();


};
