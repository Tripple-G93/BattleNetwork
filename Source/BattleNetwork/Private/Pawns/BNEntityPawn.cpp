// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNEntityPawn.h"

#include "Actors/BNGridActor.h"
#include "ActorComponents/BNPaperFlipbookComponent.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Objects/BNUtilityStatics.h"
#include "SceneComponents/BNEntityWidgetSceneComponent.h"

#include <AbilitySystemComponent.h>
#include <Components/AudioComponent.h>
#include <Components/BoxComponent.h>
#include <Components/SceneComponent.h>
#include <Net/UnrealNetwork.h>
#include <Sound/SoundCue.h>

ABNEntityPawn::ABNEntityPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	BNPaperFlipbookComponent = ObjectInitializer.CreateDefaultSubobject<UBNPaperFlipbookComponent>(this, TEXT("BNPaperFlipbookComponent"));
	BNPaperFlipbookComponent->SetupAttachment(SceneComponent);
	BNPaperFlipbookComponent->bReplicatePhysicsToAutonomousProxy = false;
	BNPaperFlipbookComponent->SetIsReplicated(true);

	EntityWidgetSceneComponent = ObjectInitializer.CreateDefaultSubobject<UBNEntityWidgetSceneComponent>(this, TEXT("EntityWidgetSceneComponent"));
	EntityWidgetSceneComponent->SetupAttachment(BNPaperFlipbookComponent);

	BoxComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(EntityWidgetSceneComponent);

	AudioComponent = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this,TEXT("AudioComponent"));
	
	SpriteOffset.X = 0;
	SpriteOffset.Y = 0;
	SpriteOffset.Z = 0;
	
	bCanMove = true;
}

void ABNEntityPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABNEntityPawn, TeamTag);
	DOREPLIFETIME(ABNEntityPawn, GridActorReference);
	DOREPLIFETIME(ABNEntityPawn, ServerGridLocation);
}

void ABNEntityPawn::UpdateAnimation(FGameplayTag AnimationTag)
{
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
        CurrentFlipbookAnimationTableInfoRow, BNPaperFlipbookComponent, AnimationTag);
}

void ABNEntityPawn::PlayAnimationSoundEffect() const
{
	USoundCue* SoundEffectCue = CurrentFlipbookAnimationTableInfoRow->SoundEffectSoundCue;
	if(SoundEffectCue)
	{
		AudioComponent->SetSound(SoundEffectCue);
		AudioComponent->Play();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't play Gameplay Tag animation sound effect %s"), *CurrentFlipbookAnimationTableInfoRow->AnimationGameplayTag.ToString());
	}
}

bool ABNEntityPawn::CanEntityMove()
{
    const UAbilitySystemComponent* GameplayAbilitySystemComponent = GetAbilitySystemComponent();
    return !GameplayAbilitySystemComponent->HasMatchingGameplayTag(AbilityGameplayTag) && !GameplayAbilitySystemComponent->HasMatchingGameplayTag(MovementGameplayTag);
}

void ABNEntityPawn::AttemptToMoveLeft()
{
    if (MoveEntityLeftRPC_Validate())
    {
        BNPaperFlipbookComponent->OnFoundSocket.AddDynamic(this, &ABNEntityPawn::ClientCallMoveEntityLeftRPC);
        BNPaperFlipbookComponent->SocketToLookFor(MoveSpriteSocketName);
        UpdateMoveAnimationRPC();
    }
}

void ABNEntityPawn::AttemptToMoveRight()
{
    if (MoveEntityRightRPC_Validate())
    {
        BNPaperFlipbookComponent->OnFoundSocket.AddDynamic(this, &ABNEntityPawn::ClientCallMoveEntityRightRPC);
        BNPaperFlipbookComponent->SocketToLookFor(MoveSpriteSocketName);
        UpdateMoveAnimationRPC();
    }
}

void ABNEntityPawn::AttemptToMovePlayerEntityHorizontally(const float Value)
{
    if (CanEntityMove())
    {
        if (Value < 0)
        {
            AttemptToMoveLeft();
        }
        else if (Value > 0)
        {
            AttemptToMoveRight();
        }
    }
}

void ABNEntityPawn::AttemptToMovePlayerEntityVertically(const float Value)
{
    const UAbilitySystemComponent* GameplayAbilitySystemComponent = GetAbilitySystemComponent();
    if (bCanMove && GameplayAbilitySystemComponent && !GameplayAbilitySystemComponent->HasMatchingGameplayTag(AbilityGameplayTag))
    {
        if (Value > 0)
        {
            if (MoveEntityUpRPC_Validate())
            {
                bCanMove = false;
                UpdateMoveAnimationRPC();
                UpdateMoveAnimationRPC_Implementation();
                BNPaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNEntityPawn::ClientCallMoveEntityUpRPC);
            }
        }
        else if (Value < 0)
        {
            if (MoveEntityDownRPC_Validate())
            {
                bCanMove = false;
                UpdateMoveAnimationRPC();
                UpdateMoveAnimationRPC_Implementation();
                BNPaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNEntityPawn::ClientCallMoveEntityDownRPC);
            }
        }
    }
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

FVector3d ABNEntityPawn::GetSpriteOffset() const
{
	return SpriteOffset;
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

UBNPaperFlipbookComponent* ABNEntityPawn::GetBNPaperFlipbookComponent()
{
	return BNPaperFlipbookComponent;
}

void ABNEntityPawn::SetActorHiddenInGame(bool bNewHidden)
{
    Super::SetActorHiddenInGame(bNewHidden);

    if (bNewHidden)
    {
        BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
    else
    {
        BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
}

/*
 * End Getters
 */

void ABNEntityPawn::BeginPlay()
{
	Super::BeginPlay();
	
	BNPaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNEntityPawn::UpdateIdleAnimation);
}

void ABNEntityPawn::InitializeAttributes()
{
	Super::InitializeAttributes();

	EntityWidgetSceneComponent->InitializeEntityUserWidget();

	BNPaperFlipbookComponent->SetPlayRate(AttributeSetBase->GetSpeedPercentRate());
}

void ABNEntityPawn::EnableMovementIfStandaloneMode()
{
	if(GetLocalRole() == ROLE_Authority)
	{
		bCanMove = true;
	}
}

void ABNEntityPawn::UpdateIdleAnimation()
{
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
CurrentFlipbookAnimationTableInfoRow, BNPaperFlipbookComponent, IdleAnimationGameplayTag);
	BNPaperFlipbookComponent->PlayFromStart();

	if(GetAbilitySystemComponent()->HasMatchingGameplayTag(MovementGameplayTag))
	{
		GetAbilitySystemComponent()->RemoveLooseGameplayTag(MovementGameplayTag);
	}
}

void ABNEntityPawn::ClientCallMoveEntityLeftRPC(FTransform SocketTransform)
{
    BNPaperFlipbookComponent->OnFoundSocket.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityLeftRPC);

	MoveEntityLeftRPC();
}

void ABNEntityPawn::ClientCallMoveEntityRightRPC(FTransform SocketTransform)
{
	BNPaperFlipbookComponent->OnFoundSocket.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityRightRPC);

	MoveEntityRightRPC();
}

void ABNEntityPawn::ClientCallMoveEntityUpRPC()
{
	BNPaperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityUpRPC);

	MoveEntityUpRPC();
}

void ABNEntityPawn::ClientCallMoveEntityDownRPC()
{
	BNPaperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &ABNEntityPawn::ClientCallMoveEntityDownRPC);

	MoveEntityDownRPC();
}

/*
 * Server RPC
 */

void ABNEntityPawn::UpdateMoveAnimationRPC_Implementation()
{
	if(!GetAbilitySystemComponent()->HasMatchingGameplayTag(MovementGameplayTag))
	{
		GetAbilitySystemComponent()->AddLooseGameplayTag(MovementGameplayTag);
	}
	
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
	CurrentFlipbookAnimationTableInfoRow, BNPaperFlipbookComponent, MovementGameplayTag);
	
	BNPaperFlipbookComponent->PlayFromStart();
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