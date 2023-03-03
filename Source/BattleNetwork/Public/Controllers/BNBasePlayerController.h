// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "BNBasePlayerController.generated.h"

class UBNGameMusicAudioComponent;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(VisibleAnywhere, Replicated)
    TObjectPtr<UBNGameMusicAudioComponent> GameMusicAudioComponent;

public:

    ABNBasePlayerController();

    UFUNCTION(Client, Reliable)
    void PlayGameMusic(FGameplayTag GameMusicGameplayTag);

    UFUNCTION(Client, Reliable)
    void RandomlyPlayGameMusic();

    void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

};
