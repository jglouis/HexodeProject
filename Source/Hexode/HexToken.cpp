// hexode.xyz

#include "Hexode.h"
#include "HexToken.h"
#include "HexCoordinate.h"
#include <math.h>

// Sets default values
AHexToken::AHexToken()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	this->Coord.U = U;
	this->Coord.V = V;
}

void AHexToken::SetHexCoordinate(FHexCoordinate NewCoord)
{
	this->Coord = NewCoord;
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

			float Angle = UHexUtil::Angle(MovementVector, CurrentHexCoordinate);

			if (Speed <= MaxSpeed && Acceleration <= MaxAcceleration && Angle <=  PI / 3.0 * Maneuvrabililty)
			{
				ValidVectors.Add(CurrentHexCoordinate);
			}			
		}
	}

	return ValidVectors;
}
