// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNPlayerPawn.h"

#include "PaperFlipbookComponent.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "BattleNetwork/BattleNetwork.h"
#include "PlayerStates/BNPlayerState.h"

// Sets default values
ABNPlayerPawn::ABNPlayerPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ASCInputBound = false;
}

void ABNPlayerPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializePlayerGameplayAbilitySystem();
}

// Called to bind functionality to input
void ABNPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move_Horizontal", this, &ABNPlayerPawn::AttemptToMovePlayerEntityHorizontally);
	InputComponent->BindAxis("Move_Verticle", this, &ABNPlayerPawn::AttemptToMovePlayerEntityVertically);

	// Bind player input to the AbilitySystemComponent. Also called in SetupPlayerInputComponent because of a potential race condition.
	BindASCInput();
}

void ABNPlayerPawn::AttemptToMovePlayerEntityHorizontally(const float Value)
{
	const UAbilitySystemComponent* GameplayAbilitySystemComponent = GetAbilitySystemComponent();
	if(bCanMove && GameplayAbilitySystemComponent && !GameplayAbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Entity.Ability"))))
	{
		if(Value < 0)
		{
			if(MoveEntityLeftRPC_Validate())
			{
				bCanMove = false;
				UpdateMoveAnimationRPC();
				UpdateMoveAnimationRPC_Implementation();
				PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNPlayerPawn::ClientCallMoveEntityLeftRPC);
			}
		}
		else if(Value > 0)
		{
			if(MoveEntityRightRPC_Validate())
			{
				bCanMove = false;
				UpdateMoveAnimationRPC();
				UpdateMoveAnimationRPC_Implementation();
				PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNPlayerPawn::ClientCallMoveEntityRightRPC);
			}
		}
	}
}

void ABNPlayerPawn::AttemptToMovePlayerEntityVertically(const float Value)
{
	const UAbilitySystemComponent* GameplayAbilitySystemComponent = GetAbilitySystemComponent();
	if(bCanMove && GameplayAbilitySystemComponent && !GameplayAbilitySystemComponent->HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Entity.Ability"))))
	{
		if(Value > 0)
		{
			if(MoveEntityUpRPC_Validate())
			{
				bCanMove = false;
				UpdateMoveAnimationRPC();
				UpdateMoveAnimationRPC_Implementation();
				PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNPlayerPawn::ClientCallMoveEntityUpRPC);
			}
		}
		else if(Value < 0)
		{
			if(MoveEntityDownRPC_Validate())
			{
				bCanMove = false;
				UpdateMoveAnimationRPC();
				UpdateMoveAnimationRPC_Implementation();
				PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &ABNPlayerPawn::ClientCallMoveEntityDownRPC);
			}
		}
	}
}

void ABNPlayerPawn::BindASCInput()
{
	if (!ASCInputBound && IsValid(AbilitySystemComponent) && IsValid(InputComponent))
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("EGSAbilityInputID"), static_cast<int32>(EGSAbilityInputID::Confirm), static_cast<int32>(EGSAbilityInputID::Cancel)));

		ASCInputBound = true;
	}
}

// Client only
void ABNPlayerPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializePlayerGameplayAbilitySystem();

	const ABNPlayerState* BNPlayerState = GetPlayerState<ABNPlayerState>();
	if(ensure(BNPlayerState))
	{
		// Bind player input to the AbilitySystemComponent. Also called in SetupPlayerInputComponent because of a potential race condition.
		BindASCInput();
	}
}


