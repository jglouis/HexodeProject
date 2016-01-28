// hexode.xyz

#pragma once

#include "GameFramework/Actor.h"
#include "HexCoordinate.h"
#include "HexBoard.generated.h"

UCLASS()
class HEXODE_API AHexBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexBoard();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Get the World location from hexagonal coordinates
	UFUNCTION(BlueprintPure, Category = "Board")
	FVector GetWorldLocationFromHexCoordinate(FHexCoordinate Coord) const;

	// Get the hexagonal coordinate from World location
	UFUNCTION(BlueprintPure, Category = "Board")
	FHexCoordinate GetHexCoordFromWorldLocation(FVector location) const;	

	// Display a tile at the given hexagonal coordinate
	UFUNCTION(BlueprintCallable, Category = "Board")
	void DisplayTile(FHexCoordinate Coord);

	// Display a valid location tile at the given hexagonal coordinate
	UFUNCTION(BlueprintCallable, Category = "Board")
	void DisplayValidLocationTile(FHexCoordinate Coord);

	// Add a Token on the board and position it to the apropriate transform location
	UFUNCTION(BlueprintCallable, Category = "Board")
	void AddToken(class AHexToken* Token);

protected:
	// The Radius from center
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	uint8 Radius;

	// The Radius from center
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	uint8 TileSize;

private:
	// The instanced static mesh that represents the hexagonal board
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", Meta = (AllowPrivateAccess = "true"))
	class UInstancedStaticMeshComponent* BoardMesh;

	// The instanced static mesh that represents the valid movement locations on the hexagonal board
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", Meta = (AllowPrivateAccess = "true"))
	class UInstancedStaticMeshComponent* ValidLocationsBoardMesh;

	// The static mesh representing the mesh when cursor is over
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", Meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CursorOverBoardMesh;

	// The collision boc
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", Meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionBox;

	// An array of all the tokens on the board
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", Meta = (AllowPrivateAccess = "true"))
	TArray<class AHexToken*> Tokens;

	// Update the board visible locations
	UFUNCTION(BlueprintCallable, Category = "Board")
	void UpdateVisibleLocations();

};
