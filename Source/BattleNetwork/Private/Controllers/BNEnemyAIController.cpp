// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNEnemyAIController.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h>

void ABNEnemyAIController::BeginPlay()
{
    Super::BeginPlay();

}

ABNEnemyAIController::ABNEnemyAIController(const FObjectInitializer& ObjectInitializer)
{
    TimeRemainingToAttackName = "TimeRemainingToAttack";
}

void ABNEnemyAIController::StartBehaviorTree()
{
    if (ensure(BehaviorTree))
    {
        RunBehaviorTree(BehaviorTree);
    }

    GetBlackboardComponent()->SetValueAsFloat(TimeRemainingToAttackName, 2.5);
}

void ABNEnemyAIController::StopBehaviorTree()
{
    if (ensure(BehaviorTree))
    {
        UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
        if (BehaviorTreeComponent != nullptr)
        {
            BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
        }
    }
}
