// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeInitial.h"

#include "Actors/BNGridActor.h"
#include "Actors/BNProjectilePool.h"
#include "Controllers/BNPlayerController.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Pawns/BNEntityPawn.h"
#include "Subsystems/BNSessionSubsystem.h"

void ABNGameModeInitial::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    SpawnGridActor();

    SpawnObjectPool();

    GridActor->InitializeGrid();
}

void ABNGameModeInitial::SpawnGridActor()
{
    if (ensure(GridActorSubClass))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = this;
        SpawnParameters.OverrideLevel = GetLevel();

        GridActor = GetWorld()->SpawnActor<ABNGridActor>(GridActorSubClass, FVector(0, 0, 0), FRotator(0, 0, 0), SpawnParameters);
    }
}

void ABNGameModeInitial::SpawnObjectPool()
{
    if (ensure(BulletProjectilePoolSubClass))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = this;
        SpawnParameters.OverrideLevel = GetLevel();

        BulletProjectilePool = GetWorld()->SpawnActor<ABNProjectilePool>(BulletProjectilePoolSubClass, SpawnParameters);
    }
}

void ABNGameModeInitial::CreatePlayer(APlayerController* NewPlayer, int XGridLocation, int YGridLocation)
{
    ABNEntityPawn* entityPawn = GridActor->CreateEntityAtLocation(PlayerEntityTag, XGridLocation, YGridLocation);
    entityPawn->SetOwner(NewPlayer);

    NewPlayer->Possess(entityPawn);
    NewPlayer->SetViewTarget(GridActor);

    entityPawn->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");

    PlayerPawn = entityPawn;
}

void ABNGameModeInitial::GameHasEnded(AController* Controller)
{
    // We want to end the multiplayer session here
    UBNSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UBNSessionSubsystem>();
    SessionSubsystem->EndSession();

    // Do a check if player controller is null because that means it was an enemy ai
    // (This will change once we establish real game rules and establish who has won)
    if (!Controller)
    {
        Cast<ABNPlayerController>(PlayerControllers[0])->DisplayWinResultUI();
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

TObjectPtr<ABNProjectilePool> ABNGameModeInitial::GetBulletProjectilePool()
{
    return BulletProjectilePool;
}

ABNGridActor* ABNGameModeInitial::GetGridActor()
{
    return GridActor;
}

ABNEntityPawn* ABNGameModeInitial::GetPlayerPawn()
{
    return PlayerPawn;
}
