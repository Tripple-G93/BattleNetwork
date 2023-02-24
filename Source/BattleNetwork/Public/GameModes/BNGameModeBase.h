// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BNGameModeBase.generated.h"

class UBNGameMusicAudioComponent;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

    UPROPERTY(VisibleAnywhere, Replicated)
    TObjectPtr<UBNGameMusicAudioComponent> GameMusicAudioComponent;

public:

    ABNGameModeBase();

    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
