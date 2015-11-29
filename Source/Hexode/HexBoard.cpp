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

FVector AHexBoard::GetWorldLocationFromHexagonalCoordinates(int32 U, int32 V) const
{
	float X = this->TileSize * sqrt(3) * (U + V / 2.0f);
	float Y = this->TileSize * 1.5f * V;

	return FVector(X,Y,0.0f);
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
	FVector Vector = this->GetWorldLocationFromHexagonalCoordinates(U, V);
	FTransform Transform = FTransform(Vector);
	// Spawn the instance
	BoardMesh->AddInstance(Transform);
}

void AHexBoard::AddToken(AHexToken* Token)
{
	// Adding the token to the array
	this->Tokens.Add(Token);

	// Place the token on the appropriate coordinates
	TArray<int32> HexCoord = Token->GetUV();
	int32 U = HexCoord[0];
	int32 V = HexCoord[1];
	FVector Vector = this->GetWorldLocationFromHexagonalCoordinates(U, V);

	// Set target move location for the token
	this->MoveToken(Token, U, V);
}

void AHexBoard::MoveToken(AHexToken * Token, int32 U, int32 V)
{	
	if (Token && this->Tokens.Contains(Token)) {
		FVector Vector= this->GetWorldLocationFromHexagonalCoordinates(U, V);
		Token->SetTargetMoveLocation(Vector);
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

	for (AHexToken* Token : this->Tokens)
	{
		int32 U = Token->GetUV()[0];
		int32 V = Token->GetUV()[1];

		FHexCoordinate Coordinate(U,V);

		this->DisplayTile(U, V);
		// Iterate over all the tiles around the token locations

	}
}
