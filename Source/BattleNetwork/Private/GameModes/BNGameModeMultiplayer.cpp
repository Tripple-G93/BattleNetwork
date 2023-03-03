// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeMultiplayer.h"

#include "Actors/BNGridActor.h"
#include "Actors/BNProjectilePool.h"
#include "ActorComponents/BNGameMusicAudioComponent.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNPlayerController.h"
#include "Engine/World.h"
#include "Subsystems/BNSessionSubsystem.h"

ABNGameModeMultiplayer::ABNGameModeMultiplayer()
{
    MaxPlayersOnGrid = 2;
}


void ABNGameModeMultiplayer::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    SpawnGrid();

    SpawnObjectPool();

    GridActor->CreateGrid();
}

void ABNGameModeMultiplayer::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    // Test to see if I can change this from the one that is inherited from instead.
    MultiPlayerControllers.Add(NewPlayer);

    ABNBasePlayerController* BasePlayerController = Cast<ABNBasePlayerController>(NewPlayer);
    if (BasePlayerController)
    {
        BasePlayerController->RandomlyPlayGameMusic();
    }
    // I think for now we want to be able to  play the music through here but when we have an offical start to the game mode we want ot iterate through all the added controllers

    if (MultiPlayerControllers.Num() == 1)
    {
        GridActor->SpawnPlayer1(NewPlayer);
        GridActor->GetPlayer1Pawn()->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");
    }
    else if (MultiPlayerControllers.Num() == 2)
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

    for (int index = 0; index < MultiPlayerControllers.Num(); ++index)
    {
        if (Controller != MultiPlayerControllers[index])
        {
            Cast<ABNPlayerController>(MultiPlayerControllers[index])->DisplayWinResultUI();
        }
        else
        {
            Cast<ABNPlayerController>(MultiPlayerControllers[index])->DisplayLossResultUI();
        }
    }
}

void ABNGameModeMultiplayer::BeginPlay()
{
    Super::BeginPlay();  
}

int ABNGameModeMultiplayer::GetMaxPlayersOnGrid() const
{
    return MaxPlayersOnGrid;
}

TArray<APlayerController*>& ABNGameModeMultiplayer::GetPlayerControllers()
{
    return PlayerControllers;
}

TObjectPtr<ABNProjectilePool> ABNGameModeMultiplayer::GetBulletProjectilePool()
{
    return BulletProjectilePool;
}

ABNGridActor* ABNGameModeMultiplayer::GetGridActor()
{
    return GridActor;
}

void ABNGameModeMultiplayer::SpawnGrid()
{
    if (ensure(GridActorSubClass))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = this;
        SpawnParameters.OverrideLevel = GetLevel();

        GridActor = GetWorld()->SpawnActor<ABNGridActor>(GridActorSubClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParameters);
    }
}

void ABNGameModeMultiplayer::SpawnObjectPool()
{
    if (ensure(BulletProjectilePoolSubClass))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = this;
        SpawnParameters.OverrideLevel = GetLevel();

        BulletProjectilePool = GetWorld()->SpawnActor<ABNProjectilePool>(BulletProjectilePoolSubClass, SpawnParameters);
    }
}
