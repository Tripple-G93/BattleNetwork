// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeInitial.h"

#include "Actors/BNGridActor.h"
#include "Actors/BNProjectilePool.h"

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

TObjectPtr<ABNProjectilePool> ABNGameModeInitial::GetBulletProjectilePool()
{
    return BulletProjectilePool;
}

ABNGridActor* ABNGameModeInitial::GetGridActor()
{
    return GridActor;
}
