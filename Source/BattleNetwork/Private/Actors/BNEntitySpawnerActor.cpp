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
	PrimaryActorTick.bCanEverTick = true;

}

ABNEntityPawn* ABNEntitySpawnerActor::SpawnEntity(FGameplayTag EntityTag)
{
    if (ensure(SpawnableEntityDataTable))
    {
        FBNSpawnableEntityTableInfoRow* Row = SpawnableEntityDataTable->FindRow<FBNSpawnableEntityTableInfoRow>(EntityTag.GetTagName(), TEXT("Trying to spawn an entity"));
        if (ensure(Row))
        {
            ABNEntityPawn* NewEntity = GetWorld()->SpawnActor<ABNEntityPawn>(Row->EntityPawn);
            if (ensure(NewEntity))
            {
                Entities.Add(NewEntity);
                return NewEntity;
            }
        }
    }

    return nullptr;
}

// Called when the game starts or when spawned
void ABNEntitySpawnerActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABNEntitySpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

