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

}

// Client only
void ABNPlayerPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializePlayerGameplayAbilitySystem();
}

