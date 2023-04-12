// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeSinglePlayer.h"

#include "Actors/BNGridActor.h"
#include "Actors/BNProjectilePool.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNPlayerController.h"
#include "Engine/World.h"
#include "Pawns/BNPlayerPawn.h"
#include "Subsystems/BNSessionSubsystem.h"

void ABNGameModeSinglePlayer::PostLogin(APlayerController* NewPlayer)
{
    ABNBasePlayerController* BasePlayerController = Cast<ABNBasePlayerController>(NewPlayer);
    if (BasePlayerController)
    {
        BasePlayerController->RandomlyPlayGameMusic();
    }

    GridActor->SpawnPlayer1(NewPlayer);
    GridActor->GetPlayer1Pawn()->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");

    GridActor->CreateEntity(EnemyEntityTag, 4, 1);
}

void ABNGameModeSinglePlayer::GameHasEnded(AController* Controller)
{
    // We want to end the multiplayer session here
    UBNSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UBNSessionSubsystem>();
    SessionSubsystem->EndSession();

    // Do a check if player controller is null then return and honestly do an ensure because that should not be the case
    if (!ensure(Controller))
    {
        return;
    }

    for (int index = 0; index < PlayerControllers.Num(); ++index)
    {
        if (Controller != PlayerControllers[index])
        {
            Cast<ABNPlayerController>(PlayerControllers[index])->DisplayWinResultUI();
        }
        else
        {
            Cast<ABNPlayerController>(PlayerControllers[index])->DisplayLossResultUI();
        }
    }
}

