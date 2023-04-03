// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeBase.h"


ABNGameModeBase::ABNGameModeBase()
{}

void ABNGameModeBase::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    PlayerControllers.Add(NewPlayer);
}

TArray<APlayerController*>& ABNGameModeBase::GetPlayerControllers()
{
    return PlayerControllers;

}