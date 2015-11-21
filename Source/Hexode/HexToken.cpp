// Fill out your copyright notice in the Description page of Project Settings.

#include "Hexode.h"
#include "HexToken.h"


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

void AHexToken::SetUV(int32 U, int32 V)
{
	this->U = U;
	this->V = V;
}

