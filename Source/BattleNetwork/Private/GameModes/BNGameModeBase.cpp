// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeBase.h"

#include "ActorComponents/BNGameMusicAudioComponent.h"
#include <Net/UnrealNetwork.h>

ABNGameModeBase::ABNGameModeBase()
{
    GameMusicAudioComponent = CreateDefaultSubobject<UBNGameMusicAudioComponent>(TEXT("GameMusicAudioComponent"));
}

void ABNGameModeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ABNGameModeBase, GameMusicAudioComponent);
}