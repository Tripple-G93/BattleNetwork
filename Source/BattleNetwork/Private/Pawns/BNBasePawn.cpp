// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNBasePawn.h"
#include "Objects/BNUtilityStatics.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ABNBasePawn::ABNBasePawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
}

void ABNBasePawn::UpdateAnimation(FGameplayTag NewStatus)
{
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
		CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, NewStatus);
}

// Called when the game starts or when spawned
void ABNBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABNBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABNBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

