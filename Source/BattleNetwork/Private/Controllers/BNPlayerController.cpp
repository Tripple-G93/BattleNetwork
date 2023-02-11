// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNPlayerController.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "PlayerStates/BNPlayerState.h"

void ABNPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ABNPlayerState* PS = GetPlayerState<ABNPlayerState>();
	if (PS)
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
	
}

void ABNPlayerController::DisplayResultUI()
{

}
