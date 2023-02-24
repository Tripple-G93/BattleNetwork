// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "BNGameMusicTable.generated.h"

class USoundCue;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNGameMusicTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag GameMusicGameplayTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> GameMusicSoundCue;
};
