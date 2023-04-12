// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNEntitySpawnerActor.h"

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pawns/BNEntityPawn.h"
#include "Tables/BNSpawnableEntityTable.h"

// Sets default values
ABNEntitySpawnerActor::ABNEntitySpawnerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// TODO Helper function for finding the start and end index for the search
ABNEntityPawn* ABNEntitySpawnerActor::GetEntityFromSpawner(FGameplayTag EntityTag)
{
    int startIndex = GetStartEntitiesIndex(EntityTag);
    int endIndex = GetEndEntitiesIndex(EntityTag);

    ABNEntityPawn* Entity = nullptr;
    for (int i = startIndex; i < endIndex; ++i)
    {
        ABNEntityPawn* SpawnedEntity = Entities[i];
        if (SpawnedEntity->IsHidden())
        {
            Entity = SpawnedEntity;
            break;
        }
    }

    return Entity;
}

int ABNEntitySpawnerActor::GetStartEntitiesIndex(FGameplayTag EntityTag)
{
    int startIndex = 0;
    for (const auto& EntityAmount : SpawnableEntityAmount)
    {
        if (EntityAmount.Key == EntityTag)
        {
            break;
        }

        startIndex += EntityAmount.Value;
    }

    return startIndex;
}


int ABNEntitySpawnerActor::GetEndEntitiesIndex(FGameplayTag EntityTag)
{
    int endIndex = 0;
    for (const auto& EntityAmount : SpawnableEntityAmount)
    {
        endIndex += EntityAmount.Value;

        if (EntityAmount.Key == EntityTag)
        {
            break;
        }
    }

    return endIndex;
}

void ABNEntitySpawnerActor::SpawnEntities()
{
    for (const auto& EntityAmount : SpawnableEntityAmount)
    {
        for (int i = 0; i < EntityAmount.Value; ++i)
        {
            SpawnEntity(EntityAmount.Key);
        }
    }
}

void ABNEntitySpawnerActor::SpawnEntity(FGameplayTag EntityTag)
{
    int totalAmountOfSpawnableEntities = 0;
    for (const auto& EntityAmount : SpawnableEntityAmount)
    {
        totalAmountOfSpawnableEntities += EntityAmount.Value;
    }

    Entities.Reserve(totalAmountOfSpawnableEntities);
    if (ensure(SpawnableEntityDataTable))
    {
        FBNSpawnableEntityTableInfoRow* Row = SpawnableEntityDataTable->FindRow<FBNSpawnableEntityTableInfoRow>(EntityTag.GetTagName(), TEXT("Trying to spawn an entity"));
        if (ensure(Row))
        {
            ABNEntityPawn* NewEntity = GetWorld()->SpawnActor<ABNEntityPawn>(Row->EntityPawn);
            if (ensure(NewEntity))
            {
                NewEntity->SetActorHiddenInGame(true);
                Entities.Add(NewEntity);
            }
        }
    }
}
