// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BNGameModeBase.generated.h"

class ABNGridActor;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABNGridActor> GridActorSubClass;

	UPROPERTY(EditDefaultsOnly)
	int MaxPlayersOnGrid;
	
	TObjectPtr<ABNGridActor> GridActor;

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
};
