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

	inline bool operator==(const FHexCoordinate & HexCoordinate) const
	{
		return (HexCoordinate.U == this-> U) && (HexCoordinate.V == this->V);
	}
	
};

UCLASS()
class HEXODE_API UHexUtil :	public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	/** Get the distance between two hexagonal coordinates */
	UFUNCTION(BlueprintPure, Category = "HexUtil")
	static int32 Distance(FHexCoordinate Coord1, FHexCoordinate Coord2);
};
