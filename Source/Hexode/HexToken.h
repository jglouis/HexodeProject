// hexode.xyz
#pragma once

#include "GameFramework/Actor.h"
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
	inline TArray<int32> GetUV() const { 
		TArray<int32> HexCoord = TArray<int32>();
		HexCoord.Add(U);
		HexCoord.Add(V);
		return HexCoord; }

	// Set Hexagonal coordinates
	UFUNCTION(BlueprintCallable, Category = "Token")
	void SetUV(int32 U, int32 V);

private:
	int32 U;
	int32 V;
	
};
