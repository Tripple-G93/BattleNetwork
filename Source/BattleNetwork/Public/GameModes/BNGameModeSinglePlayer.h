// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeInitial.h"
#include "BNGameModeSinglePlayer.generated.h"

class ABNEntityPawn;
class UDataTable;
struct FBNEnemyAmountTableInfoRow;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeSinglePlayer : public ABNGameModeInitial
{
	GENERATED_BODY()

private:
    
    UPROPERTY(EditDefaultsOnly, Category = "BN|Data Table")
	TObjectPtr<UDataTable> EnemyAmountPerRoundDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "BN|Data Table")
    TObjectPtr<UDataTable> EnemySpawnChanceDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "BN")
    int CurrentRound;

    FBNEnemyAmountTableInfoRow* CurrentEnemyAmountTableInfoRow;

    int EnemiesRemainingInRound;

    int EnemiesRemainingOnGrid;

public:

    virtual void PostLogin(APlayerController* NewPlayer) override;

    int GetCurrentRound() const;

    int GetEnemiesRemainingInRound() const;

protected:

    void BeginPlay() override;

private:

    void SetCurrentEnemyAmountAndTableInfoRow();

    void SpawnEnemiesOnGrid();

    void ProcessDeadEntity(ABNEntityPawn DeadEnemyEntity);

    UFUNCTION()
    void UpdateRoundStatus(ABNEntityPawn* DeadEnemyEntity);
};
