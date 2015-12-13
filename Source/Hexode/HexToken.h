// hexode.xyz
#pragma once

#include "GameFramework/Actor.h"
#include "HexCoordinate.h"
#include "HexToken.generated.h"

UCLASS()
class HEXODE_API AHexToken : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexToken();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Get the hexagonal coordinates
	UFUNCTION(BlueprintPure, Category = "Token")
	FHexCoordinate GetUVCoordinate() const;

	// Set Hexagonal coordinates
	UFUNCTION(BlueprintCallable, Category = "Token")
	void SetUV(int32 U, int32 V);

	// Set target location
	UFUNCTION(BlueprintCallable, Category = "Token")
	void SetTargetMoveLocation(FVector NewTargetLocation);

	// Get target location
	UFUNCTION(BlueprintPure, Category = "Token")
	FVector GetTargetMoveLocation() const;

	inline int32 GetTileRadius() const { return TileRadius; };

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Token")
	int32 U;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Token")
	int32 V;
	// Visible tile radius around the token when placed on the board when on the board, must be >1
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Token")
	int32 TileRadius = 3;

private:
	// Target location for the movement
	FVector TargetMoveLocation;
};
