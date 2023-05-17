// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeBase.h"
#include <GameplayTagContainer.h>
#include "BNGameModeInitial.generated.h"

class ABNGridActor;
class ABNEntityPawn;
class ABNProjectilePool;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeInitial : public ABNGameModeBase
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditDefaultsOnly, Category="BN|SubClasses")
	TSubclassOf<ABNGridActor> GridActorSubClass;

    TObjectPtr<ABNGridActor> GridActor;

    UPROPERTY(EditDefaultsOnly, Category="BN|SubClasses")
	TSubclassOf<ABNProjectilePool> BulletProjectilePoolSubClass;

        // TODO: Remove this and use a table that represents what enemies you will be going up against. 
    UPROPERTY(EditDefaultsOnly, Category = "BN|Gameplay Tags")
	FGameplayTag EnemyEntityTag;

        // TODO: Remove this and use a table that represents what enemies you will be going up against. 
    UPROPERTY(EditDefaultsOnly, Category = "BN|Gameplay Tags")
	FGameplayTag PlayerEntityTag;

    TObjectPtr<ABNProjectilePool> BulletProjectilePool;

    // TODO: Will need a proper container for this for now using it for the behavior tree
    ABNEntityPawn* PlayerPawn;

public:

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    TObjectPtr<ABNProjectilePool> GetBulletProjectilePool();

    ABNGridActor* GetGridActor();

    ABNEntityPawn* GetPlayerPawn();

protected:

    UFUNCTION()
	void GameHasEnded(AController* Controller);

    void SpawnGridActor();

    void SpawnObjectPool();

    void CreatePlayer(APlayerController* NewPlayer, int XGridLocation, int YGridLocation);
};
