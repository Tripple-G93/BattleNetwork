// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "BNSpawnableEntityTable.generated.h"

class USoundCue;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNSpawnableEntityTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag EntityType;
};
