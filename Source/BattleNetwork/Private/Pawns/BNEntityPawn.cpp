// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNEntityPawn.h"
#include "PaperFlipbookComponent.h"

ABNEntityPawn::ABNEntityPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
}

// Called when the game starts or when spawned
void ABNEntityPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABNEntityPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

