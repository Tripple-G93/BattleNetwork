// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameModes/BNGameModeInitial.h"
#include "BNGameModeSinglePlayer.generated.h"

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
    int StartingRound;

public:

    virtual void PostLogin(APlayerController* NewPlayer) override;

protected:

    void BeginPlay() override;

};
