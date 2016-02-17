// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"
#include "UMyStaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UUMyStaticLibrary : public UObject
{
	GENERATED_BODY()
	
	
public:
	/*	Start Rama code
	 *	I did not make this code myself
	 *	Credit goes to Rama
	 *	check the website below for more info
	 *	https://wiki.unrealengine.com/Trace_Functions
	*/
		static FORCEINLINE bool Trace(
			UWorld* World,
			AActor* ActorToIgnore,
			const FVector& Start,
			const FVector& End,
			FHitResult& HitOut,
			ECollisionChannel CollisionChannel = ECC_Pawn,
			bool ReturnPhysMat = false
			) {
		if (!World)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, ActorToIgnore);
		TraceParams.bTraceComplex = true;
		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

		//Ignore Actors
		TraceParams.AddIgnoredActor(ActorToIgnore);

		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		//Trace!
		//EDIT: updated from LineTraceSingle to LineTraceSingleByChannel
		World->LineTraceSingleByChannel(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
			);

		//Hit any Actor?
		return (HitOut.GetActor() != NULL);
	}
		//Trace with an Array of Actors to Ignore
		//   Ignore as many actors as you want!
		static FORCEINLINE bool Trace(
			UWorld* World,
			TArray<AActor*>& ActorsToIgnore,
			const FVector& Start,
			const FVector& End,
			FHitResult& HitOut,
			ECollisionChannel CollisionChannel = ECC_Pawn,
			bool ReturnPhysMat = false
			) {
			if (!World)
			{
				return false;
			}

			FCollisionQueryParams TraceParams(FName(TEXT("VictoryCore Trace")), true, ActorsToIgnore[0]);
			TraceParams.bTraceComplex = true;

			//TraceParams.bTraceAsyncScene = true;
			TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

			//Ignore Actors
			TraceParams.AddIgnoredActors(ActorsToIgnore);

			//Re-initialize hit info
			HitOut = FHitResult(ForceInit);

			//EDIT: updated from LineTraceSingle to LineTraceSingleByChannel
			World->LineTraceSingleByChannel(
				HitOut,		//result
				Start,	//start
				End, //end
				CollisionChannel, //collision channel
				TraceParams
				);

			return (HitOut.GetActor() != NULL);
		}
		//Component-level trace, do a trace against just 1 component
		static FORCEINLINE bool TraceComponent(
			UPrimitiveComponent* TheComp,
			const FVector& Start,
			const FVector& End,
			FHitResult& HitOut
			) {
			if (!TheComp) return false;
			if (!TheComp->IsValidLowLevel()) return false;
			//~~~~~~~~~~~~~~~~~~~~~

			FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Comp Trace")), true, NULL);
			TraceParams.bTraceComplex = true;
			//TraceParams.bTraceAsyncScene = true;
			TraceParams.bReturnPhysicalMaterial = false;

			//Ignore Actors
			//TraceParams.AddIgnoredActors(ActorsToIgnore);

			//Re-initialize hit info
			HitOut = FHitResult(ForceInit);

			return TheComp->LineTraceComponent(
				HitOut,
				Start,
				End,
				TraceParams
				);
		}
		/*	End Rama code
		*	I did not make this code myself
		*	Credit goes to Rama
		*	check the website below for more info
		*	https://wiki.unrealengine.com/Trace_Functions
		*/
};
