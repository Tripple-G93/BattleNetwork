// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <GameplayTagContainer.h>
#include "BNEnemySpawnChanceTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNEnemySpawnChanceTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 SpawnPercentChance;

    UPROPERTY(EditDefaultsOnly)
    FGameplayTag EntityGameplayTag;
};
