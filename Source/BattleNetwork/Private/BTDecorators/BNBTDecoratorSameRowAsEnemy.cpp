// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorators/BNBTDecoratorSameRowAsEnemy.h"

#include "GameModes/BNGameModeInitial.h"
#include "Pawns/BNEntityPawn.h"

#include <AIController.h>

bool UBNBTDecoratorSameRowAsEnemy::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();

    AGameModeBase* gamemode = pawn->GetWorld()->GetAuthGameMode();

    ABNGameModeInitial* bnGamemode = Cast<ABNGameModeInitial>(gamemode);
    if (ensure(bnGamemode))
    {
        ABNEntityPawn* player = bnGamemode->GetPlayerPawn();

        ABNEntityPawn* entity = Cast<ABNEntityPawn>(pawn);

        if (ensure(entity))
        {
            return player->GetServerGridLocation().YIndex == entity->GetServerGridLocation().YIndex;
        }
    }

    return false;
}
