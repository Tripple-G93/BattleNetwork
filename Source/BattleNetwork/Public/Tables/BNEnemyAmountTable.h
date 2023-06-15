// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BNEnemyAmountTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNEnemyAmountTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 EnemyAmount;

    UPROPERTY(EditDefaultsOnly)
	int32 RoundThreshold;
};
