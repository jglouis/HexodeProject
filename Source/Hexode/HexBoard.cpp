// Fill out your copyright notice in the Description page of Project Settings.

#include "Hexode.h"
#include "HexBoard.h"
#include <math.h>


// Sets default values
AHexBoard::AHexBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the instanced static mesh
	BoardMesh = CreateAbstractDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BoardMesh"));
	RootComponent = BoardMesh;

}

// Called when the game starts or when spawned
void AHexBoard::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Getting the world"));

	UWorld* const World = GetWorld();
	if (World) {
		UE_LOG(LogTemp, Warning, TEXT("We have the world"));
		// Get the actor transform
		FTransform const transform = this->GetTransform();

		UE_LOG(LogTemp, Warning, TEXT("Board's Location is %s"),
			*transform.GetLocation().ToString());

		FTransform const transform2 = FTransform(FVector(10.0f, 10.0f, 10.0f));

		// Spawn a tile
		BoardMesh->AddInstance(transform);
		BoardMesh->AddInstance(transform2);
	}

	
}

FTransform AHexBoard::GetWorldLocationFromHexagonalCoordinates(uint8 TileSize, int32 U, int32 V) const
{
	float X = TileSize * sqrt(3) * (U + V / 2.0f);
	float Y = TileSize * 1.5f * V;

	return FTransform(FVector(X,Y,0.0f));
}
