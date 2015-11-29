// hexode.xyz

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "HexCoordinate.generated.h"

/**
 * 
 */
USTRUCT()
struct FHexCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	int32 U;
	UPROPERTY()
	int32 V;
	
	FHexCoordinate();
	FHexCoordinate(int32, int32);
	
};
