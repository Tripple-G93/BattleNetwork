// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeSinglePlayer.h"

#include "Actors/BNGridActor.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNPlayerController.h"
#include "Math/RandomStream.h"
#include "Pawns/BNEntityPawn.h"
#include "Tables/BNEnemyAmountOnGridTable.h"
#include "Tables/BNEnemyAmountTable.h"
#include "Tables/BNEnemySpawnChanceTable.h"

void ABNGameModeSinglePlayer::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ABNBasePlayerController* BasePlayerController = Cast<ABNBasePlayerController>(NewPlayer);
    if (BasePlayerController)
    {
        BasePlayerController->RandomlyPlayGameMusic();
    }

    CreatePlayer(NewPlayer, 1, 1);
}

int ABNGameModeSinglePlayer::GetCurrentRound() const
{
    return CurrentRound;
}

int ABNGameModeSinglePlayer::GetEnemiesRemaining() const
{
    return EnemiesRemaining;
}

void ABNGameModeSinglePlayer::BeginPlay()
{
    SetCurrentEnemyAmountAndTableInfoRow();

    SetCurrentEnemyAmountOnGridTableInfoRow();

    TArray<FBNEnemySpawnChanceTableInfoRow*> EnemySpawnChanceTableRows;
    EnemySpawnChanceDataTable->GetAllRows<FBNEnemySpawnChanceTableInfoRow>("", EnemySpawnChanceTableRows);
    while(CurrentEnemiesOnGrid < CurrentEnemyAmountOnGridTableInfoRow->EnemyAmountOnGrid)
    {
        for (FBNEnemySpawnChanceTableInfoRow* EnemySpawnChanceTableRow : EnemySpawnChanceTableRows)
        {
            int32 RandomInt = FMath::RandRange(1, 100);
            if (RandomInt < EnemySpawnChanceTableRow->SpawnPercentChance)
            {
                ABNEntityPawn* EnemyEntityPawn = GridActor->CreateEnemyEntityAtRandomLocation(EnemySpawnChanceTableRow->EntityGameplayTag);
                EnemyEntityPawn->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");

                ++CurrentEnemiesOnGrid;
            }
        }
    }
}

void ABNGameModeSinglePlayer::SetCurrentEnemyAmountAndTableInfoRow()
{
    TArray<FBNEnemyAmountTableInfoRow*> EnemyAmountTableRows;
    EnemyAmountPerRoundDataTable->GetAllRows<FBNEnemyAmountTableInfoRow>("", EnemyAmountTableRows);

    for (FBNEnemyAmountTableInfoRow* EnemyAmountTableRow : EnemyAmountTableRows)
    {
        if (CurrentRound <= EnemyAmountTableRow->RoundThreshold)
        {
            CurrentEnemyAmountTableInfoRow = EnemyAmountTableRow;
            EnemiesRemaining = EnemyAmountTableRow->EnemyAmount;
            break;
        }
    }
}

void ABNGameModeSinglePlayer::SetCurrentEnemyAmountOnGridTableInfoRow()
{
    TArray<FBNEnemyAmountOnGridTableInfoRow*> EnemyAmountOnGridTableRows;
    EnemyAmountOnGridPerRoundDataTable->GetAllRows<FBNEnemyAmountOnGridTableInfoRow>("", EnemyAmountOnGridTableRows);

    for (FBNEnemyAmountOnGridTableInfoRow* EnemyAmountOnGridTableRow : EnemyAmountOnGridTableRows)
    {
        if (CurrentRound <= EnemyAmountOnGridTableRow->RoundThreshold)
        {
            CurrentEnemyAmountOnGridTableInfoRow = EnemyAmountOnGridTableRow;
            break;
        }
    }
}
