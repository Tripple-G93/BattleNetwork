// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeSinglePlayer.h"

#include "Actors/BNGridActor.h"
#include "Controllers/BNPlayerController.h"

void ABNGameModeSinglePlayer::PostLogin(APlayerController* NewPlayer)
{
    ABNBasePlayerController* BasePlayerController = Cast<ABNBasePlayerController>(NewPlayer);
    if (BasePlayerController)
    {
        BasePlayerController->RandomlyPlayGameMusic();
    }

    CreatePlayer(NewPlayer, 1, 1);

    GridActor->CreateEntity(EnemyEntityTag, 4, 1);
}