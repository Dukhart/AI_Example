// Copyright Jordan Duncan 2016

#pragma once

#include "Object.h"

// for debugging
#include "DrawDebugHelpers.h"

#include "AIE_StaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class AI_EXAMPLE_API UAIE_StaticLibrary : public UObject
{
	GENERATED_BODY()


public:
	/*	Start Rama code
	*	I did not make this code myself
	*	Credit goes to Rama
	*	check the website below for more info
	*	https://wiki.unrealengine.com/Trace_Functions
	*	
	*	I did ad minor edit to linetracesingle updating the function call
	*	Also added debug draw line option
	*/
	static FORCEINLINE bool Trace(
		UWorld* World,
		AActor* ActorToIgnore,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		ECollisionChannel CollisionChannel = ECC_Pawn,
		bool ReturnPhysMat = false, 
		bool bDrawDebug = false, float debugDrawDuration = 10.0f
		) {
		if (!World)
		{
			return false;
		}
		
		

		FCollisionQueryParams TraceParams(FName(TEXT("Trace")), true, ActorToIgnore);
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
		// MYEDIT added debug draw
		if (bDrawDebug) {
			// where we hit
			DrawDebugLine(World, Start, HitOut.ImpactPoint, FColor::Red, false, debugDrawDuration, 0, 5.0f);
			// complete line from attemped trace start to end
			DrawDebugLine(World, Start, End, FColor::Yellow, false, debugDrawDuration);
		}

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
		bool ReturnPhysMat = false,
		bool bDrawDebug = false, float debugDrawDuration = 10.0f
		) {
		if (!World)
		{
			return false;
		}

		FCollisionQueryParams TraceParams(FName(TEXT("Trace Ignore Array")), true, ActorsToIgnore[0]);
		TraceParams.bTraceComplex = true;

		//TraceParams.bTraceAsyncScene = true;
		TraceParams.bReturnPhysicalMaterial = ReturnPhysMat;

		//Ignore Actors
		TraceParams.AddIgnoredActors(ActorsToIgnore);

		//Re-initialize hit info
		HitOut = FHitResult(ForceInit);

		//MYEDIT: updated from LineTraceSingle to LineTraceSingleByChannel
		World->LineTraceSingleByChannel(
			HitOut,		//result
			Start,	//start
			End, //end
			CollisionChannel, //collision channel
			TraceParams
			);
		// MYEDIT added debug draw
		if (bDrawDebug) {
			// where we hit
			DrawDebugLine(World, Start, HitOut.ImpactPoint, FColor::Red, false, debugDrawDuration, 0, 5.0f);
			// complete line from attemped trace start to end
			DrawDebugLine(World, Start, End, FColor::Yellow, false, debugDrawDuration);
		}

		return (HitOut.GetActor() != NULL);
	}
	//Component-level trace, do a trace against just 1 component
	static FORCEINLINE bool TraceComponent(
		UPrimitiveComponent* TheComp,
		const FVector& Start,
		const FVector& End,
		FHitResult& HitOut,
		bool bDrawDebug = false, float debugDrawDuration = 10.0f
		) {
		if (!TheComp) return false;
		if (!TheComp->IsValidLowLevel()) return false;
		//~~~~~~~~~~~~~~~~~~~~~

		FCollisionQueryParams TraceParams(FName(TEXT("Comp Trace")), true, NULL);
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
		// MYEDIT added debug draw
		UWorld* World = TheComp->GetWorld();
		if (bDrawDebug && World) {
			
			// where we hit
			DrawDebugLine(World, Start, HitOut.ImpactPoint, FColor::Red, false, debugDrawDuration, 0, 5.0f);
			// complete line from attemped trace start to end
			DrawDebugLine(World, Start, End, FColor::Yellow, false, debugDrawDuration);
		}
	}
	/*	End Rama code
	*	I did not make this code myself
	*	Credit goes to Rama
	*	check the website below for more info
	*	https://wiki.unrealengine.com/Trace_Functions
	*/
};

