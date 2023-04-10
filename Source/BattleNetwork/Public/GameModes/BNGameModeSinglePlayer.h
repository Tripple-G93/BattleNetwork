// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeInitial.h"
#include "BNGameModeSinglePlayer.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeSinglePlayer : public ABNGameModeInitial
{
	GENERATED_BODY()
	
public:

    virtual void PostLogin(APlayerController* NewPlayer) override;

    UFUNCTION()
	void GameHasEnded(AController* Controller);
};