// hexode.xyz
#pragma once

#include "GameFramework/Actor.h"
#include "HexCoordinate.h"
#include "HexBoard.h"
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

	inline int32 GetTileRadius() const { return TileRadius; };

	// Get a list of all the valid movementVectors
	UFUNCTION(BlueprintPure, Category = "Token")
	TArray<FHexCoordinate> GetValidMovementVectors();

	void SetBoard(class AHexBoard* Board);

protected:
	//Hex Coordinate
	UPROPERTY(ReplicatedUsing=OnCoord_Rep, EditAnywhere, BlueprintReadOnly, Category = "Token")
	FHexCoordinate Coord;

	//Target move location
	UPROPERTY(BlueprintReadOnly, Category = "Token")
	FVector TargetMoveLocation;

	// Movement Vector
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Token")
	FHexCoordinate MovementVector;

	// Max Acceleration
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Token")
	int32 MaxAcceleration;

	// Max Speed (maximum length of the movement vector)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Token")
	int32 MaxSpeed;

	// Maneuverability (limits the deviation for the new movement vector)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Token")
	int32 Maneuverabililty;

	// Visible tile radius around the token when placed on the board when on the board, must be >1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Token")
	int32 TileRadius = 3;

	// Pointer to the board
	UPROPERTY(BlueprintReadOnly, Category = "Token")
	AHexBoard* Board;

private:
	UFUNCTION()
	void OnCoord_Rep();
	
	// Recompute the target move location according to hexagonal coordinates of the token
	void UpdateTargetMoveLocation();

};
