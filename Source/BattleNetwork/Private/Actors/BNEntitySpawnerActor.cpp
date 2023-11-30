// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNEntitySpawnerActor.h"

#include "Pawns/BNEntityPawn.h"
#include "Tables/BNSpawnableEntityTable.h"

#include <GameFramework/Actor.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>

// Sets default values
ABNEntitySpawnerActor::ABNEntitySpawnerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

ABNEntityPawn* ABNEntitySpawnerActor::GetEntityFromSpawner(FGameplayTag EntityTag)
{
    TArray<ABNEntityPawn*>& EntityArray = EntityMap[EntityTag];

    for (ABNEntityPawn* Entity : EntityArray)
    {
        if (Entity->IsHidden())
        {
            return Entity;
        }
    }

    return EntityArray[0];
}

void ABNEntitySpawnerActor::SpawnEntities()
{
    for (const auto& EntityAmount : SpawnableEntityAmount)
    {
        EntityMap.Add(EntityAmount.Key, TArray<ABNEntityPawn*>());
        EntityMap[EntityAmount.Key].Reserve(EntityAmount.Value);
        for (int i = 0; i < EntityAmount.Value; ++i)
        {
            SpawnEntity(EntityAmount.Key, i);
        }
    }
}

void ABNEntitySpawnerActor::SpawnEntity(FGameplayTag EntityTag, int Index)
{
    if (ensure(SpawnableEntityDataTable))
    {
        FBNSpawnableEntityTableInfoRow* Row = SpawnableEntityDataTable->FindRow<FBNSpawnableEntityTableInfoRow>(EntityTag.GetTagName(), TEXT("Trying to spawn an entity"));
        if (ensure(Row))
        {
            FVector Location(0.f, 5.f * Index, 100.f);
            FRotator Rotation(0.f, 0.0f, 0.f);
            FVector Scale(1.f, 1.f, 1.f);
            FTransform SpawnTransform(Rotation, Location, Scale);

            ABNEntityPawn* NewEntity = GetWorld()->SpawnActor<ABNEntityPawn>(Row->EntityPawn, SpawnTransform);
            if (ensure(NewEntity))
            {
                NewEntity->SetActorHiddenInGame(true);
                NewEntity->SetActorEnableCollision(false);
                EntityMap[EntityTag].Add(NewEntity);
            }
        }
    }
}
