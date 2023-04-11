// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNEntityPawn.h"

#include "AbilitySystemComponent.h"
#include "Actors/BNGridActor.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Objects/BNUtilityStatics.h"
#include "PaperFlipbookComponent.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "SceneComponents/BNEntityWidgetSceneComponent.h"
#include "Sound/SoundCue.h"

ABNEntityPawn::ABNEntityPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	PaperFlipbookComponent = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);
	PaperFlipbookComponent->bReplicatePhysicsToAutonomousProxy = false;
	PaperFlipbookComponent->SetIsReplicated(true);

	EntityWidgetSceneComponent = ObjectInitializer.CreateDefaultSubobject<UBNEntityWidgetSceneComponent>(this, TEXT("EntityWidgetSceneComponent"));
	EntityWidgetSceneComponent->SetupAttachment(PaperFlipbookComponent);

	BoxComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(EntityWidgetSceneComponent);

	AudioComponent = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this,TEXT("AudioComponent"));
	
	SpriteOffset.X = 0;
	SpriteOffset.Y = 0;
	SpriteOffset.Z = 0;
	
	bCanMove = true;
}

void ABNEntityPawn::FlipEntity()
{
	FVector LocationOffset = PaperFlipbookComponent->GetRelativeLocation();
	LocationOffset.Y *= -1;
	PaperFlipbookComponent->SetRelativeLocation(LocationOffset);

	LocationOffset = EntityWidgetSceneComponent->GetRelativeLocation();
	LocationOffset.X *= -1;
	EntityWidgetSceneComponent->SetRelativeLocation(LocationOffset);
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
CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, AnimationTag);
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

TObjectPtr<UPaperFlipbookComponent> ABNEntityPawn::GetPaperFlipbookComponent()
{
	return PaperFlipbookComponent;
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

	if(TeamTag == FGameplayTag::RequestGameplayTag("Team2"))
	{
		FlipEntity();
	}
	
	PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNEntityPawn::UpdateIdleAnimation);
}

void ABNEntityPawn::InitializeAttributes()
{
	Super::InitializeAttributes();

	EntityWidgetSceneComponent->InitializeEntityUserWidget();

	PaperFlipbookComponent->SetPlayRate(AttributeSetBase->GetSpeedPercentRate());
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
CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, FGameplayTag::RequestGameplayTag(FName("Entity.Idle")));
	PaperFlipbookComponent->PlayFromStart();

	const FGameplayTag MoveGameplayTag = FGameplayTag::RequestGameplayTag(FName("Entity.Move"));
	if(GetAbilitySystemComponent()->HasMatchingGameplayTag(MoveGameplayTag))
	{
		GetAbilitySystemComponent()->RemoveLooseGameplayTag(MoveGameplayTag);
	}
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
	const FGameplayTag MoveGameplayTag = FGameplayTag::RequestGameplayTag(FName("Entity.Move"));
	if(!GetAbilitySystemComponent()->HasMatchingGameplayTag(MoveGameplayTag))
	{
		GetAbilitySystemComponent()->AddLooseGameplayTag(MoveGameplayTag);
	}
	
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
	CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, MoveGameplayTag);
	
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