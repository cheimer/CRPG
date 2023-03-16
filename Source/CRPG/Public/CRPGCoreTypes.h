#pragma once
#include "CRPGCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EScreenMode : uint8
{
	Field = 0,
	Battle, 
	GamePause,
	GameOver
};

UENUM(BlueprintType)
enum class ETurnUser : uint8
{
	Player = 0,
	Enemy
};
