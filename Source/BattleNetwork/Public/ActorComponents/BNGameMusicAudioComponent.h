// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "Tables/BNGameMusicTable.h"
#include "BNGameMusicAudioComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNGameMusicAudioComponent : public UAudioComponent
{
	GENERATED_BODY()

protected:

    UPROPERTY(EditDefaultsOnly, Category = "BN")
	TObjectPtr<UDataTable> GameMusicDataTable;

public:

    void PlayGameMusic(FGameplayTag GameMusicGameplayTag);

    void RandomlyPlayGameMusic();
	
};
