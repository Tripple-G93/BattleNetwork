// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNEnemyAIController.h"

void ABNEnemyAIController::RunOwnBehaviorTree()
{
    if (ensure(BehaviorTree))
    {
        RunBehaviorTree(BehaviorTree);
    }
}
