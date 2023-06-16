// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeInitial.h"
#include "BNGameModeSinglePlayer.generated.h"

struct FBNEnemyAmountOnGridTableInfoRow;
struct FBNEnemyAmountTableInfoRow;
class UDataTable;

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

    UPROPERTY(EditDefaultsOnly, Category = "BN|Data Table")
    TObjectPtr<UDataTable> EnemyAmountOnGridPerRoundDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "BN")
    int CurrentRound;

    FBNEnemyAmountTableInfoRow* CurrentEnemyAmountTableInfoRow;

    FBNEnemyAmountOnGridTableInfoRow* CurrentEnemyAmountOnGridTableInfoRow;

    int EnemiesRemaining;

    int EnemiesAllowedOnGrid;

public:

    virtual void PostLogin(APlayerController* NewPlayer) override;

    int GetCurrentRound() const;

    int GetEnemiesRemaining() const;

protected:

    void BeginPlay() override;

private:

    void SetCurrentEnemyAmountAndTableInfoRow();

    void SetCurrentEnemyAmountOnGridTableInfoRow();

};
