// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include <GameplayTagContainer.h>
#include "BNBTTaskNodeFireProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBTTaskNodeFireProjectile : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditAnywhere, Category = "BN|Gameplay Tag")
    FGameplayTag SkillGameplayTag;

private:

    EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
