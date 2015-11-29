// hexode.xyz

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "HexCoordinate.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHexCoordinate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 U;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 V;
	
	FHexCoordinate();
	FHexCoordinate(int32, int32);
	
};
