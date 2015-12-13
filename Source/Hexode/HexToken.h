// hexode.xyz
#pragma once

#include "GameFramework/Actor.h"
#include "HexCoordinate.h"
#include "HexToken.generated.h"

UCLASS()
class HEXODE_API AHexToken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexToken();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Get the hexagonal coordinates
	UFUNCTION(BlueprintPure, Category = "Token")
	FHexCoordinate GetHexCoordinate() const;

	// Set Hexagonal coordinates
	UFUNCTION(BlueprintCallable, Category = "Token")
	void SetUV(int32 U, int32 V);

	// Set Hexagonal coordinates
	UFUNCTION(BlueprintCallable, Category = "Token")
	void SetHexCoordinate(FHexCoordinate NewCoord);

	// Set target location
	UFUNCTION(BlueprintCallable, Category = "Token")
	void SetTargetMoveLocation(FVector NewTargetLocation);

	// Get target location
	UFUNCTION(BlueprintPure, Category = "Token")
	FVector GetTargetMoveLocation() const;

	inline int32 GetTileRadius() const { return TileRadius; };

protected:
	//Hex Coordinate
	FHexCoordinate Coord;

	// Visible tile radius around the token when placed on the board when on the board, must be >1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Token")
	int32 TileRadius = 3;

private:
	// Target location for the movement
	FVector TargetMoveLocation;
};
