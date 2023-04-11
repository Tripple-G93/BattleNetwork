// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Containers/Map.h"
#include "GameplayTagContainer.h"

#include "BNEntitySpawnerActor.generated.h"

class ABNEntityPawn;
class UDataTable;

UCLASS()
class BATTLENETWORK_API ABNEntitySpawnerActor : public AActor
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditDefaultsOnly, Category = "BN|Spawner")
	TObjectPtr<UDataTable> SpawnableEntityDataTable;

    UPROPERTY(EditAnywhere, Category = "BN|Spawner")
    TMap<FGameplayTag, int> SpawnableEntityAmount;

    TArray<ABNEntityPawn*> Entities;

public:	
	// Sets default values for this actor's properties
	ABNEntitySpawnerActor();

    void SpawnEntities();

    ABNEntityPawn* GetEntityFromSpawner(FGameplayTag EntityTag);

protected:

    void SpawnEntity(FGameplayTag EntityTag);

};
