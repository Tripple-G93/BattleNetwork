// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BNEnemyAmountOnGridTable.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNEnemyAmountOnGridTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 EnemyAmountOnGrid;

    UPROPERTY(EditDefaultsOnly)
	int32 RoundThreshold;
};
