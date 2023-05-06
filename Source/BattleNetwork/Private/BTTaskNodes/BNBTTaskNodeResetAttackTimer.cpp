// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNodes/BNBTTaskNodeResetAttackTimer.h"

#include "BehaviorTree/BlackboardComponent.h"

UBNBTTaskNodeResetAttackTimer::UBNBTTaskNodeResetAttackTimer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TimeRemainingToAttackName = "TimeRemainingToAttack";

    DefaultTimeRemainingToAttackValue = 2.0f;
}

EBTNodeResult::Type UBNBTTaskNodeResetAttackTimer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // TODO: Right now it will be an exposed variable but can we have it be a default from the tree?
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TimeRemainingToAttackName, DefaultTimeRemainingToAttackValue);

    return EBTNodeResult::Succeeded;
}
