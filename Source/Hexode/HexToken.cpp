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
	bReplicates = true;

}

// Called when the game starts or when spawned
void AHexToken::BeginPlay()
{
	Super::BeginPlay();
	
}

FHexCoordinate AHexToken::GetUVCoordinate() const
{
	FHexCoordinate Coord;
	Coord.U = this->U;
	Coord.V = this->V;
	return Coord;
}

void AHexToken::SetUV(int32 U, int32 V)
{
	this->U = U;
	this->V = V;
}

void AHexToken::SetTargetMoveLocation(FVector NewTargetLocation)
{
	this->TargetMoveLocation = NewTargetLocation;

	if (Role < ROLE_Authority)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not the server"));
		ServerSetTargetMoveLocation(NewTargetLocation);
	}
}

FVector AHexToken::GetTargetMoveLocation() const
{
	return this->TargetMoveLocation;
}

void AHexToken::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	DOREPLIFETIME(AHexToken, U);
	DOREPLIFETIME(AHexToken, V);
	DOREPLIFETIME(AHexToken, TargetMoveLocation)
}

bool AHexToken::ServerSetTargetMoveLocation_Validate(FVector NewTargetMoveLocation)
{
	return true;
}

void AHexToken::ServerSetTargetMoveLocation_Implementation(FVector NewTargetMoveLocation)
{
	// This function is only called on the server (where Role == ROLE_Authority), called over the network by clients.
	// We need to call SetSomeBool() to actually change the value of the bool now!
	// Inside that function, Role == ROLE_Authority, so it won't try to call ServerSetSomeBool() again.
	UE_LOG(LogTemp, Warning, TEXT("Running on the server"));
	TargetMoveLocation = NewTargetMoveLocation;
}

