// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorators/BNBTDecoratorIsEntityDead.h"

#include "Pawns/BNEntityPawn.h"

#include <AIController.h>

bool UBNBTDecoratorIsEntityDead::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();
    ABNEntityPawn* entity = Cast<ABNEntityPawn>(pawn);

    return entity->IsEntityDead();
}
