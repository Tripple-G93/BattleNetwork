// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNBasePlayerController.h"

#include "ActorComponents/BNGameMusicAudioComponent.h"

#include <Net/UnrealNetwork.h>

static TAutoConsoleVariable<bool> CVarEnableGameMusic(TEXT("bn.EnableGameMusic"), false, TEXT("Enable Game Music"), ECVF_Cheat);

ABNBasePlayerController::ABNBasePlayerController()
{
    GameMusicAudioComponent = CreateDefaultSubobject<UBNGameMusicAudioComponent>(TEXT("GameMusicAudioComponent"));
    GameMusicAudioComponent->SetIsReplicated(true);
}

// Client Implementation
void ABNBasePlayerController::PlayGameMusic_Implementation(FGameplayTag GameMusicGameplayTag)
{
    if (GameMusicAudioComponent && CVarEnableGameMusic.GetValueOnGameThread())
    {
        GameMusicAudioComponent->PlayGameMusic(GameMusicGameplayTag);
    }
}

// Client Implementation
void ABNBasePlayerController::RandomlyPlayGameMusic_Implementation()
{
    if (GameMusicAudioComponent && CVarEnableGameMusic.GetValueOnGameThread())
    {
        GameMusicAudioComponent->RandomlyPlayGameMusic();
    }
}

void ABNBasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABNBasePlayerController, GameMusicAudioComponent);
}