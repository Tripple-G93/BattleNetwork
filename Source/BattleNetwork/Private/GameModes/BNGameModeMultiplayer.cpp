// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeMultiplayer.h"

#include "Controllers/BNPlayerController.h"

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
        CreatePlayer(NewPlayer, 1, 1);
    }
    else if (PlayerControllers.Num() == 2)
    {
        CreatePlayer(NewPlayer, 4, 1);
    }
}

