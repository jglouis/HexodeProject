// hexode.xyz

#include "Hexode.h"
#include "HexBoard.h"
#include <math.h>
#include "HexToken.h"


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

FTransform AHexBoard::GetWorldLocationFromHexagonalCoordinates(int32 U, int32 V) const
{
	float X = this->TileSize * sqrt(3) * (U + V / 2.0f);
	float Y = this->TileSize * 1.5f * V;

	return FTransform(FVector(X,Y,0.0f));
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
	FTransform transform = this->GetWorldLocationFromHexagonalCoordinates(U, V);
	
	// Spawn the instance
	BoardMesh->AddInstance(transform);
}

void AHexBoard::AddToken(AHexToken* Token)
{
	// Adding the token to the array
	this->Tokens.Add(Token);

	// Place the token on the appropriate coordinates
	TArray<int32> HexCoord = Token->GetUV();
	int32 U = HexCoord[0];
	int32 V = HexCoord[1];
	FTransform transform = this->GetWorldLocationFromHexagonalCoordinates(U, V);
	Token->SetActorTransform(transform);
}

TArray<class AHexToken*> AHexBoard::GetTokens() const
{
	return TArray<class AHexToken*>();
}
