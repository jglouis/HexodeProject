// hexode.xyz

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "HexCoordinate.h"
#include "Weapon.generated.h"

/**
 * Structure representing a weapon.
 */
USTRUCT(BlueprintType)
struct HEXODE_API FWeapon
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Strength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<struct FHexCoordinate> Coordinates;
	
};
