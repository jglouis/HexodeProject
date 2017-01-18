// hexode.xyz

#include "Hexode.h"
#include "HexToken.h"
#include "HexCoordinate.h"
#include <math.h>
#include "UnrealNetwork.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red,text)

// Sets default values
AHexToken::AHexToken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

void AHexToken::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHexToken, Coord);
	DOREPLIFETIME(AHexToken, Board);
	DOREPLIFETIME(AHexToken, Weapons);
	DOREPLIFETIME(AHexToken, OwnerId);
}

// Called when the game starts or when spawned
void AHexToken::BeginPlay()
{
	Super::BeginPlay();
	
}

FHexCoordinate AHexToken::GetHexCoordinate() const
{
	return Coord;
}

void AHexToken::SetUV(int32 U, int32 V)
{
	Coord.U = U;
	Coord.V = V;
}

void AHexToken::SetHexCoordinate(FHexCoordinate NewCoord)
{
	Coord = NewCoord;

	// Update target move location explicitly on the authority
	if (Role == ROLE_Authority)
	{
		UpdateTargetMoveLocation();
	}
}

TArray<FHexCoordinate> AHexToken::GetValidMovementVectors()
{
	TArray<FHexCoordinate> ValidVectors = TArray<FHexCoordinate>();
	
	// Iterate over every coordinates limited by MaxSpeed
	for (int32 u = -MaxSpeed; u <= MaxSpeed; u++)
	{
		for (int32 v = -MaxSpeed; v <= MaxSpeed; v++)
		{
			FHexCoordinate CurrentHexCoordinate(u, v);
			int32 Speed = UHexUtil::Amplitude(CurrentHexCoordinate);
			int32 OldSpeed = UHexUtil::Amplitude(MovementVector);
			int32 Acceleration = Speed - OldSpeed;
			int32 Deviation = UHexUtil::Distance(CurrentHexCoordinate, MovementVector);

			if (Speed <= MaxSpeed && Acceleration <= MaxAcceleration && Deviation <= Maneuverabililty)
			{
				ValidVectors.Add(CurrentHexCoordinate);
			}			
		}
	}

	return ValidVectors;
}

void AHexToken::SetBoard(AHexBoard * NewBoard)
{
	this->Board = NewBoard;
}

void AHexToken::OnCoord_Rep()
{
	UpdateTargetMoveLocation();
}

void AHexToken::UpdateTargetMoveLocation()
{
	if (Board) {
		TargetMoveLocation = Board->GetWorldLocationFromHexCoordinate(Coord);
	}
	else {
		print("Board not assigned");
	}
}

