// Copyright Jordan Duncan 2016

#include "AI_Example.h"
#include "AIE_AISenseConfig_Sight.h"



// 0 is infinate age
// clamped between 0 and 10 000
void UAIE_AISenseConfig_Sight::SetMaxAge(float newMaxAge) {
	MaxAge = FMath::Clamp(newMaxAge, 0.0f, 10000.0f);
}