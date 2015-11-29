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
	RootComponent = BoardMesh;

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

int32 AHexBoard::GetUFromWorldLocation(FVector location) const
{
	float X = location.X;
	float Y = location.Y;

	return round((X * sqrt(3.0f) / 3.0f - Y / 3.0f) / this->TileSize);
}

int32 AHexBoard::GetVFromWorldLocation(FVector location) const
{
	float Y = location.Y;

	return round(Y * 2.0f / 3.0f / this->TileSize);
}

int32 AHexBoard::Distance(int32 U1, int32 V1, int32 U2, int32 V2) const
{
	return (abs(U1 - U2)
		+ abs(U1 + V1 - U2 - V2)
		+ abs(V1 - V2)) / 2;
}

void AHexBoard::DisplayTile(int32 U, int32 V)
{
	// Get the transform location
	FVector Vector = this->GetWorldLocationFromHexCoordinate(FHexCoordinate(U,V)); //TODO
	FTransform Transform = FTransform(Vector);
	// Spawn the instance
	BoardMesh->AddInstance(Transform);
}

void AHexBoard::AddToken(AHexToken* Token)
{
	// Adding the token to the array
	this->Tokens.Add(Token);

	// Place the token on the appropriate coordinates
	int32 U = Token->GetUVCoordinate().U;
	int32 V = Token->GetUVCoordinate().V;
	FVector Vector = this->GetWorldLocationFromHexCoordinate(Token->GetUVCoordinate());

	// Set target move location for the token
	this->MoveToken(Token, U, V);
}

void AHexBoard::MoveToken(AHexToken * Token, int32 U, int32 V)
{	
	if (Token && this->Tokens.Contains(Token)) {
		FVector Vector= this->GetWorldLocationFromHexCoordinate(FHexCoordinate(U, V));
		// Set tokens's target move location
		Token->SetTargetMoveLocation(Vector);
		// Set token's UV location
		Token->SetUV(U, V);
	}
	else {
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
		const int VisionRadius = 3;
		for (int u = U - VisionRadius; u <= U + VisionRadius; u++)
		{
			for (int v = V - VisionRadius; v <= V + VisionRadius; v++)
			{
				if (this->Distance(U, V, u, v) <= 3)
				{
					FHexCoordinate CoordinateToAdd(u,v);
					// Add the coordinate uniquely so a tile is not displayed twice
					Coordinates.AddUnique(CoordinateToAdd);
				}				
			}
		}
	}

	// Display the tiles in the set
	for (FHexCoordinate CoordToDisplay : Coordinates)
	{
		this->DisplayTile(CoordToDisplay.U, CoordToDisplay.V);
	}
}
