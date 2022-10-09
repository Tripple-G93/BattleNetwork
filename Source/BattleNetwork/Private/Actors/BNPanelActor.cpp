// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNPanelActor.h"
#include "Components/SceneComponent.h"
#include "Objects/BNUtilityStatics.h"
#include "PaperFlipbookComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABNPanelActor::ABNPanelActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);
	PaperFlipbookComponent->bReplicatePhysicsToAutonomousProxy = false;
	PaperFlipbookComponent->SetIsReplicated(true);
}

void ABNPanelActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABNPanelActor, EntityPawn);
}

void ABNPanelActor::SetEntityPawn(ABNEntityPawn* NewEntityPawn)
{
	EntityPawn = NewEntityPawn;
}

TObjectPtr<ABNEntityPawn> ABNPanelActor::GetEntityPawn()
{
	return EntityPawn;
}

void ABNPanelActor::SetPanelStatus(FGameplayTag NewStatus)
{
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
		CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, NewStatus);
}

