// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeMainMenu.h"

#include "ActorComponents/BNGameMusicAudioComponent.h"

void ABNGameModeMainMenu::BeginPlay()
{
    Super::BeginPlay();
    
    GameMusicAudioComponent->RandomlyPlayGameMusic();
}
