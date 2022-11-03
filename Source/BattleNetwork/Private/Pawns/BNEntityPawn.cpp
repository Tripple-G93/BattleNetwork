// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNEntityPawn.h"

#include "AbilitySystemComponent.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "Actors/BNGridActor.h"
#include "Components/SceneComponent.h"
#include "Objects/BNUtilityStatics.h"
#include "PaperFlipbookComponent.h"
#include "Net/UnrealNetwork.h"
#include "SceneComponents/BNEntityWidgetSceneComponent.h"

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

	EntityWidgetSceneComponent = ObjectInitializer.CreateDefaultSubobject<UBNEntityWidgetSceneComponent>(this, TEXT("EntityWidgetSceneComponent"));
	EntityWidgetSceneComponent->SetupAttachment(PaperFlipbookComponent);
	
	bCanMove = true;
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
	DOREPLIFETIME(ABNEntityPawn, ServerGridLocation);
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

void ABNEntityPawn::SetServerGridLocation(FBNGridLocation NewServerGridLocation)
{
	ServerGridLocation = NewServerGridLocation;
}

/*
 * Getters
 */

FGameplayTag ABNEntityPawn::GetTeamTag() const
{
	return TeamTag;
}

FBNGridLocation ABNEntityPawn::GetServerGridLocation() const
{
	return ServerGridLocation;
}

/*
 * End Getters
 */

void ABNEntityPawn::BeginPlay()
{
	Super::BeginPlay();

	PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNEntityPawn::UpdateAnimation);
}

void ABNEntityPawn::EnableMovementIfStandaloneMode()
{
	if(GetLocalRole() == ROLE_Authority)
	{
		bCanMove = true;
	}
}

void ABNEntityPawn::UpdateAnimation()
{
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, FGameplayTag::RequestGameplayTag(FName("Entity.Idle")));
	PaperFlipbookComponent->SetFlipbook(CurrentFlipbookAnimationTableInfoRow->PaperFlipbook);
	PaperFlipbookComponent->SetLooping(CurrentFlipbookAnimationTableInfoRow->bDoesLoop);
	PaperFlipbookComponent->PlayFromStart();
}

void ABNEntityPawn::ClientCallMoveEntityLeftRPC()
{
	PaperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityLeftRPC);

	MoveEntityLeftRPC();
}

void ABNEntityPawn::ClientCallMoveEntityRightRPC()
{
	PaperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityRightRPC);

	MoveEntityRightRPC();
}

void ABNEntityPawn::ClientCallMoveEntityUpRPC()
{
	PaperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityUpRPC);

	MoveEntityUpRPC();
}

void ABNEntityPawn::ClientCallMoveEntityDownRPC()
{
	PaperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityDownRPC);

	MoveEntityDownRPC();
}

/*
 * Server RPC
 */

void ABNEntityPawn::UpdateMoveAnimationRPC_Implementation()
{
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
	CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, FGameplayTag::RequestGameplayTag(FName("Entity.Move")));
	
	PaperFlipbookComponent->SetFlipbook(CurrentFlipbookAnimationTableInfoRow->PaperFlipbook);
	PaperFlipbookComponent->SetLooping(CurrentFlipbookAnimationTableInfoRow->bDoesLoop);
	PaperFlipbookComponent->PlayFromStart();	
}

void ABNEntityPawn::MoveEntityLeftRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, ServerGridLocation.XIndex - 1, ServerGridLocation.YIndex);

	EnableMovementIfStandaloneMode();
}

bool ABNEntityPawn::MoveEntityLeftRPC_Validate()
{
	return GridActorReference->CanEntityMoveLeft(this);
}

void ABNEntityPawn::MoveEntityRightRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, ServerGridLocation.XIndex + 1, ServerGridLocation.YIndex);

	EnableMovementIfStandaloneMode();
}

bool ABNEntityPawn::MoveEntityRightRPC_Validate()
{
	return GridActorReference->CanEntityMoveRight(this);
}

void ABNEntityPawn::MoveEntityUpRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, ServerGridLocation.XIndex, ServerGridLocation.YIndex + 1);

	EnableMovementIfStandaloneMode();
}

bool ABNEntityPawn::MoveEntityUpRPC_Validate()
{
	return GridActorReference->CanEntityMoveUp(this);
}

void ABNEntityPawn::MoveEntityDownRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, ServerGridLocation.XIndex, ServerGridLocation.YIndex - 1);

	EnableMovementIfStandaloneMode();
}

bool ABNEntityPawn::MoveEntityDownRPC_Validate()
{
	return GridActorReference->CanEntityMoveDown(this);
}

/*
 * REP_Notify
 */

void ABNEntityPawn::OnRep_UpdateClientLocation()
{
	// TODO BN: This check exist because of spawning and replication issues at the beginning of the game remove when fixed
	if(GridActorReference)
	{
		GridActorReference->MoveEntityToNewPanel(this, ServerGridLocation.XIndex, ServerGridLocation.YIndex);
	}
	bCanMove = true;
}