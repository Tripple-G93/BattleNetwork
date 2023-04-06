// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNEnemyAIController.h"

void ABNEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
    
    if(ensure(BehaviorTree))
    {
        RunBehaviorTree(BehaviorTree);
    }
}
