// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BNGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

    TArray<APlayerController*> PlayerControllers;

public:

    ABNGameModeBase();

    void PostLogin(APlayerController* NewPlayer) override;

    TArray<APlayerController*>& GetPlayerControllers();
};
