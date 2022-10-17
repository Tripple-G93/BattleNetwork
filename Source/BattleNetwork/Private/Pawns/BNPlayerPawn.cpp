// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNPlayerPawn.h"

#include "PlayerStates/BNPlayerState.h"
#include "ActorComponents/BNAbilitySystemComponent.h"

// Sets default values
ABNPlayerPawn::ABNPlayerPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

}

void ABNPlayerPawn::AttemptToMovePlayerEntityHorizontally(const float Value)
{
	if(!bCanNotMove)
	{
		if(Value < 0)
		{
			if(MoveEntityLeftRPC_Validate())
			{
				DisableEntityMovement();
				MoveEntityLeftRPC_Implementation();
				MoveEntityLeftRPC();
			}
		}
		else if(Value > 0)
		{
			if(MoveEntityRightRPC_Validate())
			{
				DisableEntityMovement();
				MoveEntityRightRPC_Implementation();
				MoveEntityRightRPC();
			}
		}
	}
}

void ABNPlayerPawn::AttemptToMovePlayerEntityVertically(const float Value)
{
	if(!bCanNotMove)
	{
		if(Value > 0)
		{
			if(MoveEntityUpRPC_Validate())
			{
				DisableEntityMovement();
				MoveEntityUpRPC_Implementation();
				MoveEntityUpRPC();
			}
		}
		else if(Value < 0)
		{
			if(MoveEntityDownRPC_Validate())
			{
				DisableEntityMovement();
				MoveEntityDownRPC_Implementation();
				MoveEntityDownRPC();
			}
		}
	}
}

// Client only
void ABNPlayerPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializePlayerGameplayAbilitySystem();
}

