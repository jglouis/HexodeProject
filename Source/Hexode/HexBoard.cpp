// hexode.xyz

#include "Hexode.h"
#include "HexBoard.h"
#include <math.h>
#include "HexToken.h"
#include "HexCoordinate.h"
#include "UnrealNetwork.h"


// Sets default values
AHexBoard::AHexBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the instanced static mesh
	BoardMesh = CreateAbstractDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("BoardMesh"));
	BoardMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Create the instanced static mesh for valid locations
	ValidLocationsBoardMesh = CreateAbstractDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ValidLocationsBoardMesh"));
	ValidLocationsBoardMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Create the instanced static mesh for arc of fire locations
	ArcOfFireBoardMesh = CreateAbstractDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ArcOfFireBoardMesh"));
	ArcOfFireBoardMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Define the root component as a collision box
	CollisionBox = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	// Create the selection static mesh
	CursorOverBoardMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(TEXT("CursorOverBoardMesh"));
	CursorOverBoardMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	bReplicates = true;	

}

void AHexBoard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHexBoard, Tokens);
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

void AHexBoard::DisplayTile(FHexCoordinate Coord, UInstancedStaticMeshComponent* InstancedBoardMesh)
{
	// Get the transform location
	FVector Vector = this->GetWorldLocationFromHexCoordinate(Coord);
	FTransform Transform = FTransform(Vector);
	// Spawn the instance
	InstancedBoardMesh->AddInstance(Transform);
}

void AHexBoard::AddToken(AHexToken* Token)
{
	// Adding the token to the array
	this->Tokens.Add(Token);
	Token->SetBoard(this);
	Token->UpdateTargetMoveLocation();
}

void AHexBoard::UpdateVisibleLocations()
{
	// Clear all the instances
	this->BoardMesh->ClearInstances();
	this->ArcOfFireBoardMesh->ClearInstances();

	// Set that will contain all the coordinates to display (no double)
	TArray<FHexCoordinate> VisibleLocationsCoordinates = TArray<FHexCoordinate>();
	TArray<FHexCoordinate> ArcOfFireCoordinates = TArray<FHexCoordinate>();

	for (AHexToken* Token : Tokens)
	{
		// Get token coordinates
		int32 U = Token->GetHexCoordinate().U;
		int32 V = Token->GetHexCoordinate().V;

		// Check if it an owned token
		UWorld* World = GetWorld();
		bool isTokenOwned = false;
		if (World) {
			isTokenOwned = World->GetFirstPlayerController()->PlayerState->PlayerId == Token->GetOwnerId();
		}

		// arc of fire
		for (FWeapon Weapon : Token->GetWeapons()) {
			for (FHexCoordinate WeaponCoordinate : Weapon.Coordinates) {
				FHexCoordinate Coord = UHexUtil::Addition(Token->GetHexCoordinate(), WeaponCoordinate);
				ArcOfFireCoordinates.AddUnique(Coord);
			}			
		}

		// Iterate over all the tiles around the token locations
		const int VisionRadius = Token->GetTileRadius();
		for (int u = U - VisionRadius; u <= U + VisionRadius; u++)
		{
			for (int v = V - VisionRadius; v <= V + VisionRadius; v++)
			{
				FHexCoordinate coord(u, v);
				// Visible locations
				if (UHexUtil::Distance(Token->GetHexCoordinate(), coord) <= VisionRadius)
				{
					// Add the coordinate uniquely so a tile is not displayed twice
					VisibleLocationsCoordinates.AddUnique(coord);					
				}
			}
		}
	}

	// Display the tiles in the set
	for (FHexCoordinate CoordToDisplay : VisibleLocationsCoordinates)
	{
		if (!ArcOfFireCoordinates.Contains(CoordToDisplay)) {
			this->DisplayTile(CoordToDisplay, BoardMesh);
		}		
	}

	// Display the tiles in the arc of fire set
	for (FHexCoordinate CoordToDisplay : ArcOfFireCoordinates)
	{
		this->DisplayTile(CoordToDisplay, ArcOfFireBoardMesh);
	}
}

