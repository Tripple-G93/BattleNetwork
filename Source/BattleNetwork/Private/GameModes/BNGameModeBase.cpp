// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeBase.h"

#include "ActorComponents/BNGameMusicAudioComponent.h"
#include <Net/UnrealNetwork.h>

ABNGameModeBase::ABNGameModeBase()
{
    GameMusicAudioComponent = CreateDefaultSubobject<UBNGameMusicAudioComponent>(TEXT("GameMusicAudioComponent"));
}

void ABNGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    RandomlyPlayGameMusic();
}

void ABNGameModeBase::RandomlyPlayGameMusic()
{
    const int RandomNumber = FMath::RandRange(0, 1);
    if (RandomNumber == 0)
    {
        GameMusicAudioComponent->PlayGameMusic(FGameplayTag::RequestGameplayTag("GameMusic.MainMenu.Hero"));
    }
    else
    {
        GameMusicAudioComponent->PlayGameMusic(FGameplayTag::RequestGameplayTag("GameMusic.MainMenu.HeroViolin"));
    }
}

void ABNGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABNGameModeBase, GameMusicAudioComponent);
}