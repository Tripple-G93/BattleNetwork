// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BNSpawnableEntityTable.generated.h"

class ABNEntityPawn;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNSpawnableEntityTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ABNEntityPawn> EntityPawn;
};
