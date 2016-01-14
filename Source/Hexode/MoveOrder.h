// hexode.xyz

#pragma once

#include "Engine/UserDefinedStruct.h"
#include "HexCoordinate.h"
#include "HexToken.h"
#include "MoveOrder.generated.h"

/**
 * Structure representing a move order.
 */
USTRUCT(BlueprintType)
struct FMoveOrder
{
	GENERATED_USTRUCT_BODY()

	// What to move
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AHexToken* Token;

	// Where to move
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FHexCoordinate Coord;	

	inline bool operator==(const FMoveOrder & MoveOrder) const
	{
		return (MoveOrder.Coord == this->Coord) && (MoveOrder.Token == this->Token);
	}
	
};
