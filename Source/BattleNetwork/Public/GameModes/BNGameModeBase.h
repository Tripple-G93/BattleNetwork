// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BNGameModeBase.generated.h"

class ABNGridActor;
class ABNProjectilePool;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeBase : public AGameModeBase
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

	ABNGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/*
	 *	Getters
	 */

	int GetMaxPlayersOnGrid() const;
	
	TArray<APlayerController*>& GetPlayerControllers();
	

private:

	void SpawnGrid();
	void SpawnObjectPool();
};
