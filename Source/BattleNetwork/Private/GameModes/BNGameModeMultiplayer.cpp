// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeMultiplayer.h"

#include "Actors/BNGridActor.h"
#include "Actors/BNProjectilePool.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNPlayerController.h"
#include "Engine/World.h"
#include "Subsystems/BNSessionSubsystem.h"

ABNGameModeMultiplayer::ABNGameModeMultiplayer()
{}

void ABNGameModeMultiplayer::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ABNBasePlayerController* BasePlayerController = Cast<ABNBasePlayerController>(NewPlayer);
    if (BasePlayerController)
    {
        BasePlayerController->RandomlyPlayGameMusic();
    }
    // I think for now we want to be able to  play the music through here but when we have an offical start to the game mode we want ot iterate through all the added controllers

    if (PlayerControllers.Num() == 1)
    {
        GridActor->SpawnPlayer1(NewPlayer);
        GridActor->GetPlayer1Pawn()->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");
    }
    else if (PlayerControllers.Num() == 2)
    {
        GridActor->SpawnPlayer2(NewPlayer);
        GridActor->GetPlayer2Pawn()->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");
    }
}

void ABNGameModeMultiplayer::GameHasEnded(AController* Controller)
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

