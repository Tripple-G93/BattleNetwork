// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNEnemyAIController.h"

#include <BehaviorTree/BlackboardComponent.h>

void ABNEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        RunOwnBehaviorTree();
    }
}

ABNEnemyAIController::ABNEnemyAIController(const FObjectInitializer& ObjectInitializer)
{
    TimeRemainingToAttackName = "TimeRemainingToAttack";
}

void ABNEnemyAIController::RunOwnBehaviorTree()
{
    if (ensure(BehaviorTree))
    {
        RunBehaviorTree(BehaviorTree);
    }

    GetBlackboardComponent()->SetValueAsFloat(TimeRemainingToAttackName, 2.5);
}
