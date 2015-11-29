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

	friend FORCEINLINE uint32 GetTypeHash(const FHexCoordinate& HexCoordinate)
	{
		return HexCoordinate.U * 100 + HexCoordinate.V;
	}

	inline bool operator==(const FHexCoordinate& HexCoordinate) const
	{
		return ((HexCoordinate.U == this-> U) && (HexCoordinate.V == this->V));
	}
	
};
