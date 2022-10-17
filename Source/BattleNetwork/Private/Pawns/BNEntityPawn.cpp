// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNEntityPawn.h"

#include "Actors/BNGridActor.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

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

	bCanNotMove = false;
}

void ABNEntityPawn::FlipEntity() const
{
	FVector LocationOffset = PaperFlipbookComponent->GetRelativeLocation();
	LocationOffset.Y *= -1;

	PaperFlipbookComponent->SetRelativeLocation(LocationOffset);
}

void ABNEntityPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABNEntityPawn, TeamTag);
	DOREPLIFETIME(ABNEntityPawn, GridActorReference);
	DOREPLIFETIME(ABNEntityPawn, XIndex);
	DOREPLIFETIME(ABNEntityPawn, YIndex);
}

/*
 * Setters
 */

void ABNEntityPawn::SetGridActorReference(ABNGridActor* GridActor)
{
	GridActorReference = GridActor;
}

void ABNEntityPawn::SetTeamTag(FGameplayTag NewTeamTag)
{
	TeamTag = NewTeamTag;
}

void ABNEntityPawn::SetNewXIndexPosition(const int32 NewXIndex)
{
	XIndex = NewXIndex;
}

void ABNEntityPawn::SetNewYIndexPosition(const int32 NewYIndex)
{
	YIndex = NewYIndex;
}

/*
 * End Setters
 */

/*
 * Getters
 */

int32 ABNEntityPawn::GetXIndexPosition() const
{
	return XIndex;
}

int32 ABNEntityPawn::GetYIndexPosition() const
{
	return YIndex;
}

FGameplayTag ABNEntityPawn::GetTeamTag() const
{
	return TeamTag;
}

/*
 * End Getters
 */

// Called when the game starts or when spawned
void ABNEntityPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABNEntityPawn::DisableEntityMovement()
{
	bCanNotMove = true;
	// TODO BN: Right now the value is hard coded and will need to be changed to the speed attribute once that is set up
	GetWorldTimerManager().SetTimer(EnableEntityMovementTimerHandler, this, &ABNEntityPawn::EnableEntityMovement, 1.0f);
}

void ABNEntityPawn::EnableEntityMovement()
{
	bCanNotMove = false;
	GetWorldTimerManager().ClearTimer(EnableEntityMovementTimerHandler);
}

/*
 * Server RPC
 */

void ABNEntityPawn::MoveEntityLeftRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, XIndex - 1, YIndex);
}

bool ABNEntityPawn::MoveEntityLeftRPC_Validate()
{
	return GridActorReference->CanEntityMoveLeft(this);
}

void ABNEntityPawn::MoveEntityRightRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, XIndex + 1, YIndex);
}

bool ABNEntityPawn::MoveEntityRightRPC_Validate()
{
	return GridActorReference->CanEntityMoveRight(this);
}

void ABNEntityPawn::MoveEntityUpRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, XIndex, YIndex - 1);
}

bool ABNEntityPawn::MoveEntityUpRPC_Validate()
{
	return GridActorReference->CanEntityMoveUp(this);
}

void ABNEntityPawn::MoveEntityDownRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, XIndex, YIndex + 1);
}

bool ABNEntityPawn::MoveEntityDownRPC_Validate()
{
	return GridActorReference->CanEntityMoveDown(this);
}