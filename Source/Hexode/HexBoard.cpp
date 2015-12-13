// hexode.xyz

#include "Hexode.h"
#include "HexBoard.h"
#include <math.h>
#include "HexToken.h"
#include "HexCoordinate.h"


// Sets default values
AHexBoard::AHexBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the instanced static mesh
	BoardMesh = CreateAbstractDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BoardMesh"));
	BoardMesh->AttachTo(RootComponent);

	// Define the root component as a collision box
	CollisionBox = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->AttachTo(RootComponent);

	// Create the selection static mesh
	CursorOverBoardMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("CursorOverBoardMesh"));
	CursorOverBoardMesh->AttachTo(RootComponent);
	

}

// Called when the game starts or when spawned
void AHexBoard::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AHexBoard::GetWorldLocationFromHexCoordinate(FHexCoordinate Coord) const
{
	float X = this->TileSize * sqrt(3) * (Coord.U + Coord.V / 2.0f);
	float Y = this->TileSize * 1.5f * Coord.V;

	return FVector(X, Y, 0.0f);
}

FHexCoordinate AHexBoard::GetHexCoordFromWorldLocation(FVector location) const
{
	float X = location.X;
	float Y = location.Y;

	int32 U = round((X * sqrt(3.0f) / 3.0f - Y / 3.0f) / this->TileSize);
	int32 V = round(Y * 2.0f / 3.0f / this->TileSize);

	return FHexCoordinate(U, V);
}

void AHexBoard::DisplayTile(FHexCoordinate Coord)
{
	// Get the transform location
	FVector Vector = this->GetWorldLocationFromHexCoordinate(Coord);
	FTransform Transform = FTransform(Vector);
	// Spawn the instance
	BoardMesh->AddInstance(Transform);
}

void AHexBoard::AddToken(AHexToken* Token)
{
	// Adding the token to the array
	this->Tokens.Add(Token);

	// Place the token on the appropriate coordinates
	FVector Vector = this->GetWorldLocationFromHexCoordinate(Token->GetUVCoordinate());

	// Set target move location for the token
	this->MoveToken(Token, Token->GetUVCoordinate());
}

void AHexBoard::MoveToken(AHexToken * Token, FHexCoordinate Coord)
{	
	UE_LOG(LogTemp, Warning, TEXT("Coordinate is (%d,%d)"), Coord.U, Coord.V);

	if (Token && this->Tokens.Contains(Token))
	{
		FVector Vector= this->GetWorldLocationFromHexCoordinate(Coord);
		// Set tokens's target move location
		Token->SetTargetMoveLocation(Vector);
		// Set token's UV location
		Token->SetUV(Coord.U, Coord.V);		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Token not valid"));
	}

	// Update the board visible locations
	this->UpdateVisibleLocations();
}

TArray<class AHexToken*> AHexBoard::GetTokens() const
{
	return TArray<class AHexToken*>();
}

void AHexBoard::UpdateVisibleLocations()
{
	// Clear all the instances
	this->BoardMesh->ClearInstances();

	// Set that will contain all the coordinates to display (no double)
	TArray<FHexCoordinate> Coordinates = TArray<FHexCoordinate>();

	for (AHexToken* Token : this->Tokens)
	{
		// Get token coordinates
		int32 U = Token->GetUVCoordinate().U;
		int32 V = Token->GetUVCoordinate().V;

		// Iterate over all the tiles around the token locations
		const int VisionRadius = Token->GetTileRadius();
		for (int u = U - VisionRadius; u <= U + VisionRadius; u++)
		{
			for (int v = V - VisionRadius; v <= V + VisionRadius; v++)
			{
				FHexCoordinate coord(u, v);
				if (UHexUtil::Distance(Token->GetUVCoordinate(), coord) <= VisionRadius)
				{
					// Add the coordinate uniquely so a tile is not displayed twice
					Coordinates.AddUnique(coord);
				}				
			}
		}
	}

	// Display the tiles in the set
	for (FHexCoordinate CoordToDisplay : Coordinates)
	{
		this->DisplayTile(CoordToDisplay);
	}
}

