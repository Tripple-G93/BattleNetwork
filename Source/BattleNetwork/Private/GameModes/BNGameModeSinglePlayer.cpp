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

    ABNPlayerController* BNPlayerController = Cast<ABNPlayerController>(NewPlayer);
    if (BNPlayerController)
    {
        BNPlayerController->RandomlyPlayGameMusic();
        BNPlayerController->CreateHud();
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
    CurrentEnemyAmountTableInfoRow = GetCurrentEnemyAmountTableInfoRow();
    if (ensure(CurrentEnemyAmountTableInfoRow))
    {
        StartRound();
    }
}

void ABNGameModeSinglePlayer::StartRound()
{
    EnemiesRemainingInRound = CurrentEnemyAmountTableInfoRow->EnemyAmountInRound;
    EnemiesRemainingOnGrid = 0;

    ABNPlayerController* BNPlayerController = Cast<ABNPlayerController>(PlayerControllers[0]);
    BNPlayerController->UpdateHudRound(CurrentRound);
    BNPlayerController->UpdateHudEnemiesRemaining(EnemiesRemainingInRound);

    SpawnEnemiesOnGrid();
}

void ABNGameModeSinglePlayer::ProceedToNextRound()
{
    ++CurrentRound;
    StartRound();
}

FBNEnemyAmountTableInfoRow* ABNGameModeSinglePlayer::GetCurrentEnemyAmountTableInfoRow()
{
    FString TableRowString = CurrentEnemyAmountTableInfoRowName.ToString() + FString::FromInt(CurrentEnemyAmountTableInfoRowNumber);

    FName TableRowName = FName(*TableRowString);

    return EnemyAmountPerRoundDataTable->FindRow<FBNEnemyAmountTableInfoRow>(TableRowName, "", false);
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
                EnemyEntityPawn->ResetAttribute();

                EnemyEntityPawn->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUniqueDynamic(this, &ABNGameModeSinglePlayer::UpdateRoundStatus);

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

    if (EnemiesRemainingInRound > 0 && EnemiesRemainingInRound > EnemiesRemainingOnGrid)
    {
        SpawnEnemiesOnGrid();
    }
    else if(EnemiesRemainingOnGrid == 0)
    {
        if (CurrentRound <= CurrentEnemyAmountTableInfoRow->RoundThreshold)
        {
            ProceedToNextRound();
        }
        else
        {
            ++CurrentEnemyAmountTableInfoRowNumber;

            CurrentEnemyAmountTableInfoRow = GetCurrentEnemyAmountTableInfoRow();
            if (CurrentEnemyAmountTableInfoRow != nullptr)
            {
                ProceedToNextRound();
            }
            else
            {
                PlayerWonGame();
            }
        }
    }
}

void ABNGameModeSinglePlayer::ProcessDeadEntity(ABNEntityPawn* DeadEnemyEntity)
{
    // TODO: When we have a death animation we will actually want to play that first before we do this
    DeadEnemyEntity->SetActorHiddenInGame(true);

    DeadEnemyEntity->GetBaseAttributeSet()->OnPlayerDeathDelegate.RemoveDynamic(this, &ABNGameModeSinglePlayer::UpdateRoundStatus);

    // TODO: Want to update this to have the ai entity be in charge of turning off it's own behavior tree and removing it from the grid before the broadcast to stop the ai from moving right after it has died but before we stop the behavior tree
    // Want to also have it responsible for turning itself itself invisible instead of having the game mode responsible for it. 
    ABNAIEntityPawn* EnemyAIEnetityPawn = Cast<ABNAIEntityPawn>(DeadEnemyEntity);
    if (ensure(EnemyAIEnetityPawn))
    {
        EnemyAIEnetityPawn->StopBehaviorTree();
    }

    GridActor->RemoveEntityFromGrid(DeadEnemyEntity);

    --EnemiesRemainingInRound;
    --EnemiesRemainingOnGrid;

    ABNPlayerController* BNPlayerController = Cast<ABNPlayerController>(PlayerControllers[0]);
    BNPlayerController->UpdateHudEnemiesRemaining(EnemiesRemainingInRound);
}
