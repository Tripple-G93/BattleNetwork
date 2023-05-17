// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodes/BNBTTaskNodeFireProjectile.h"

#include "GameModes/BNGameModeInitial.h"
#include "Pawns/BNEntityPawn.h"

#include <AbilitySystemComponent.h>
#include <AIController.h>

EBTNodeResult::Type UBNBTTaskNodeFireProjectile::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    
    APawn* pawn = OwnerComp.GetAIOwner()->GetPawn();

    ABNEntityPawn* entity = Cast<ABNEntityPawn>(pawn);

    if (ensure(entity))
    {
        FGameplayTagContainer container;
        container.AddTag(SkillGameplayTag);
        entity->GetAbilitySystemComponent()->TryActivateAbilitiesByTag(container);
    }

    return EBTNodeResult::Succeeded;
}
