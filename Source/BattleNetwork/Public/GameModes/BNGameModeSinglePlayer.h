// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeInitial.h"
#include "GameplayTagContainer.h"
#include "BNGameModeSinglePlayer.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeSinglePlayer : public ABNGameModeInitial
{
	GENERATED_BODY()
	
protected:

    // TODO: Remove this and use a table that represents what enemies you will be going up against. 
    UPROPERTY(EditDefaultsOnly, Category = "BN|Gameplay Tags")
	FGameplayTag EnemyEntityTag;

public:

    virtual void PostLogin(APlayerController* NewPlayer) override;

    UFUNCTION()
	void GameHasEnded(AController* Controller);
};
