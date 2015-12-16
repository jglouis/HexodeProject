// hexode.xyz

#include "Hexode.h"
#include "HexToken.h"
#include "HexCoordinate.h"
#include "UnrealNetwork.h"

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
