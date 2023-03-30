// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeBase.h"
#include "BNGameModeInitial.generated.h"

class ABNGridActor;
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

    TObjectPtr<ABNProjectilePool> BulletProjectilePool;

public:

    virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

    TObjectPtr<ABNProjectilePool> GetBulletProjectilePool();

    ABNGridActor* GetGridActor();

protected:

    void SpawnGridActor();

    void SpawnObjectPool();
};
