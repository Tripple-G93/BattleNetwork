// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorators/BNBTDecoratorCanAttack.h"

#include <BehaviorTree/BlackboardComponent.h>

UBNBTDecoratorCanAttack::UBNBTDecoratorCanAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TimeRemainingToAttackName = "TimeRemainingToAttack";
}

bool UBNBTDecoratorCanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

    float timeRemainingToAttack = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TimeRemainingToAttackName);
    return timeRemainingToAttack <= 0.f;
}
