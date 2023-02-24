// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeBase.h"
#include "BNGameModeMultiplayer.generated.h"

class ABNGridActor;
class ABNProjectilePool;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeMultiplayer : public ABNGameModeBase
{
	GENERATED_BODY()
	
        protected:

	UPROPERTY(EditDefaultsOnly, Category="BN|SubClasses")
	TSubclassOf<ABNGridActor> GridActorSubClass;

	UPROPERTY(EditDefaultsOnly, Category="BN|SubClasses")
	TSubclassOf<ABNProjectilePool> BulletProjectilePoolSubClass;

	UPROPERTY(EditDefaultsOnly, Category="BN|Values")
	int MaxPlayersOnGrid;
	
	TObjectPtr<ABNGridActor> GridActor;

	TObjectPtr<ABNProjectilePool> BulletProjectilePool;

	TArray<APlayerController*> PlayerControllers;

public:

    ABNGameModeMultiplayer();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION()
	void GameHasEnded(AController* Controller);

	/*
	 *	Getters
	 */

	int GetMaxPlayersOnGrid() const;
	
	TArray<APlayerController*>& GetPlayerControllers();

	TObjectPtr<ABNProjectilePool> GetBulletProjectilePool();

	ABNGridActor* GetGridActor();
	
protected:

    void BeginPlay() override;

private:

	void SpawnGrid();
	void SpawnObjectPool();
};
