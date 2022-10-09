// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNEntityPawn.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"

ABNEntityPawn::ABNEntityPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	PaperFlipbookComponent = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);
	PaperFlipbookComponent->bReplicatePhysicsToAutonomousProxy = false;
	PaperFlipbookComponent->SetIsReplicated(true);
}

void ABNEntityPawn::FlipEntity() const
{
	FVector LocationOffset = PaperFlipbookComponent->GetRelativeLocation();
	LocationOffset.Y *= -1;

	PaperFlipbookComponent->SetRelativeLocation(LocationOffset);
}

// Called when the game starts or when spawned
void ABNEntityPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


