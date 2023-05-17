// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodes/BNBTTaskNodeLineUpToOpponent.h"

#include "GameModes/BNGameModeInitial.h"
#include "Pawns/BNEntityPawn.h"

#include <AIController.h>

EBTNodeResult::Type UBNBTTaskNodeLineUpToOpponent::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();

    AGameModeBase* gamemode = pawn->GetWorld()->GetAuthGameMode();

    ABNGameModeInitial* bnGamemode = Cast<ABNGameModeInitial>(gamemode);
    if (ensure(bnGamemode))
    {
        ABNEntityPawn* player = bnGamemode->GetPlayerPawn();

        ABNEntityPawn* entity = Cast<ABNEntityPawn>(pawn);

        if (ensure(entity))
        {
            // Going to leave a note here because right now we have x and y swapped and y starts down instead of up
            if (entity->GetServerGridLocation().YIndex > player->GetServerGridLocation().YIndex)
            {
                entity->MoveEntityDownRPC();
            }
            else
            {
                entity->MoveEntityUpRPC();
            }

            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}
