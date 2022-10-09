// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNPlayerPawn.h"

// Sets default values
ABNPlayerPawn::ABNPlayerPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABNPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABNPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

