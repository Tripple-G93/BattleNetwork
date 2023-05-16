// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <GameplayTagContainer.h>
#include "BNSpawnProjectileTable.generated.h"

class ABNProjectile;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNSpawnProjectileTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag ProjectileTypeGameplayTag;

	UPROPERTY(EditDefaultsOnly)
	int32 SpawnAmount;

    UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABNProjectile> ProjectileClass;
};
