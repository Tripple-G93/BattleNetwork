// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeSinglePlayer.h"

#include "Actors/BNGridActor.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNPlayerController.h"
#include "Math/RandomStream.h"
#include "Pawns/BNEntityPawn.h"
#include "Pawns/BNAIEntityPawn.h"
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

int ABNGameModeSinglePlayer::GetEnemiesRemainingInRound() const
{
    return EnemiesRemainingInRound;
}

void ABNGameModeSinglePlayer::BeginPlay()
{
    SetCurrentEnemyAmountAndTableInfoRow();

    SpawnEnemiesOnGrid();
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
            EnemiesRemainingInRound = EnemyAmountTableRow->EnemyAmountInRound;
            EnemiesRemainingOnGrid = 0;
            break;
        }
    }
}

void ABNGameModeSinglePlayer::SpawnEnemiesOnGrid()
{
    TArray<FBNEnemySpawnChanceTableInfoRow*> EnemySpawnChanceTableRows;
    EnemySpawnChanceDataTable->GetAllRows<FBNEnemySpawnChanceTableInfoRow>("", EnemySpawnChanceTableRows);
    while (EnemiesRemainingOnGrid < CurrentEnemyAmountTableInfoRow->EnemyAmountAllowedOnGrid && EnemiesRemainingInRound > 0)
    {
        for (FBNEnemySpawnChanceTableInfoRow* EnemySpawnChanceTableRow : EnemySpawnChanceTableRows)
        {
            int32 RandomInt = FMath::RandRange(1, 100);
            if (RandomInt < EnemySpawnChanceTableRow->SpawnPercentChance)
            {
                ABNEntityPawn* EnemyEntityPawn = GridActor->CreateEnemyEntityAtRandomLocation(EnemySpawnChanceTableRow->EntityGameplayTag);
                EnemyEntityPawn->GetBaseAttributeSet()->GameModeDelegateHandle = EnemyEntityPawn->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "UpdateRoundStatus");

                ABNAIEntityPawn* EnemyAIEnetityPawn = Cast<ABNAIEntityPawn>(EnemyEntityPawn);
                if (ensure(EnemyAIEnetityPawn))
                {
                    EnemyAIEnetityPawn->StartBehaviorTree();
                }
                ++EnemiesRemainingOnGrid;
            }
        }
    }
}

void ABNGameModeSinglePlayer::UpdateRoundStatus(ABNEntityPawn* DeadEnemyEntity)
{
    ProcessDeadEntity(DeadEnemyEntity);

    if (EnemiesRemainingInRound > 0)
    {
        SpawnEnemiesOnGrid();
    }
    else
    {
        // Check if we will proceed to the next round or will end the game
        //if(CurrentRound <= )
    }

}

void ABNGameModeSinglePlayer::ProcessDeadEntity(ABNEntityPawn DeadEnemyEntity)
{
    // TODO: When we have a death animation we will actually want to play that first before we do this
    DeadEnemyEntity->SetActorHiddenInGame(true);
    // Reset the health of the enemy here
    DeadEnemyEntity->GetBaseAttributeSet()->OnPlayerDeathDelegate.Remove(DeadEnemyEntity->GetBaseAttributeSet()->GameModeDelegateHandle);

    ABNAIEntityPawn* EnemyAIEnetityPawn = Cast<ABNAIEntityPawn>(DeadEnemyEntity);
    if (ensure(EnemyAIEnetityPawn))
    {
        EnemyAIEnetityPawn->StopBehaviorTree();
    }

    --EnemiesRemainingInRound;
    --EnemiesRemainingOnGrid;

}
