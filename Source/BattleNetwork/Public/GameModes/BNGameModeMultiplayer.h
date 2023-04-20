// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeInitial.h"
#include "BNGameModeMultiplayer.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeMultiplayer : public ABNGameModeInitial
{
	GENERATED_BODY()

public:

    ABNGameModeMultiplayer();
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

};
