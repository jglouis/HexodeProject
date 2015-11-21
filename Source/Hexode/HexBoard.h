// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
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
	FTransform GetWorldLocationFromHexagonalCoordinates(int32 U, int32 V) const;

	// Get the distance between to hexagonal coordinates
	UFUNCTION(BlueprintPure, Category = "Board")
	int32 Distance(int32 U1, int32 V1, int32 U2, int32 V2) const;

	// Display a tile at the given location
	UFUNCTION(BlueprintCallable, Category = "Board")
	void DisplayTile(int32 U, int32 V);

	// Get all the tile coordinates in a given radius
	// UFUNCTION(BlueprintPure, Category = "Board")

protected:
	// The Radius from center
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	uint8 Radius;

	// The Radius from center
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Board")
	uint8 TileSize;

private:
	// The Instanced static mesh that represents the hexagonal board
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Board", Meta = (AllowPrivateAccess = "true"))
	class UInstancedStaticMeshComponent* BoardMesh;

	
};
