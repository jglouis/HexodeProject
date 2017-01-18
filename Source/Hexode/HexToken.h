// hexode.xyz
#pragma once

#include "GameFramework/Actor.h"
#include "HexCoordinate.h"
#include "OrientationEnum.h"
#include "Weapon.h"
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

	inline TArray<FWeapon> GetWeapons() const { return Weapons; };

	void SetBoard(class AHexBoard* Board);

	inline int32 GetOwnerId() const { return OwnerId; };

	// Recompute the target move location according to hexagonal coordinates of the token
	void UpdateTargetMoveLocation();

protected:
	//Current Hex Coordinate
	UPROPERTY(ReplicatedUsing=OnCoord_Rep, EditAnywhere, BlueprintReadOnly, Category = "Token")
	FHexCoordinate Coord;

	//Current orientation
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadOnly, Category = "Token")
	EOrientationEnum Orientation;

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

	// Weapons
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Token")
	TArray<FWeapon> Weapons;

	// Pointer to the board
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Token")
	AHexBoard* Board;

	// Owner's player ID
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Token")
	int32 OwnerId;

private:
	UFUNCTION()
	void OnCoord_Rep();	

};
