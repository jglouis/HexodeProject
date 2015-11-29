// hexode.xyz

#include "Hexode.h"
#include "HexToken.h"
#include "HexCoordinate.h"


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

inline FHexCoordinate AHexToken::GetUVCoordinate() const
{
	return FHexCoordinate(U, V);
}

void AHexToken::SetUV(int32 U, int32 V)
{
	this->U = U;
	this->V = V;
}

void AHexToken::SetTargetMoveLocation(FVector NewTargetLocation)
{
	this->TargetMoveLocation = NewTargetLocation;
}

FVector AHexToken::GetTargetMoveLocation() const
{
	return this->TargetMoveLocation;
}

