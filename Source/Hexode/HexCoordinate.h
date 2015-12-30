// hexode.xyz

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "Kismet/BlueprintFunctionLibrary.h"
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
	GENERATED_BODY()

public:
	/** Get the distance between two hexagonal coordinates */
	UFUNCTION(BlueprintPure, Category = "HexUtil")
	static int32 Distance(FHexCoordinate Coord1, FHexCoordinate Coord2);

	/** Get the amplitude of a hexagonal vector */
	UFUNCTION(BlueprintPure, Category = "HexUtil")
	static int32 Amplitude(FHexCoordinate Vector);

	/** Returns the angle between two hexagonal vectors*/
	UFUNCTION(BlueprintPure, Category = "HexUtil")
	static float Angle(FHexCoordinate Vector1, FHexCoordinate Vector2);

	/** Get the sum of two hexagonal coordinates */
	UFUNCTION(BlueprintPure, Category = "HexUtil")
	static FHexCoordinate Addition(FHexCoordinate Coord1, FHexCoordinate Coord2);

	/** Get the difference of two hexagonal coordinates */
	UFUNCTION(BlueprintPure, Category = "HexUtil")
	static FHexCoordinate Substraction(FHexCoordinate Coord1, FHexCoordinate Coord2);
};
