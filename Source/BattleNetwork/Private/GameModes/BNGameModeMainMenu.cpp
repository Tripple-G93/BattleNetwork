// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeMainMenu.h"

#include "ActorComponents/BNGameMusicAudioComponent.h"
#include "Controllers/BNBasePlayerController.h"

void ABNGameModeMainMenu::BeginPlay()
{
    Super::BeginPlay();
    
    if (!PlayerControllers.IsEmpty())
    {
        Cast<ABNBasePlayerController>(PlayerControllers[0])->RandomlyPlayGameMusic();
    }
}
