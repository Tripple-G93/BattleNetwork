// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNPlayerPawn.h"

#include "ActorComponents/BNAbilitySystemComponent.h"
#include "ActorComponents/BNPaperFlipbookComponent.h"
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

void ABNPlayerPawn::AttemptToMovePlayerEntityVertically(const float Value)
{
    if (CanEntityMove())
    {
        if (Value > 0)
        {
            AttemptToMoveUp();
        }
        else if (Value < 0)
        {
            AttemptToMoveDown();
        }
    }
}

void ABNPlayerPawn::BindASCInput()
{
	if (!ASCInputBound && IsValid(AbilitySystemComponent) && IsValid(InputComponent))
	{
		FTopLevelAssetPath AbilityEnumAssetPath = FTopLevelAssetPath(FName("/Script/BattleNetwork"), FName("EGSAbilityInputID"));
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), AbilityEnumAssetPath, static_cast<int32>(EGSAbilityInputID::Confirm), static_cast<int32>(EGSAbilityInputID::Cancel)));

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


