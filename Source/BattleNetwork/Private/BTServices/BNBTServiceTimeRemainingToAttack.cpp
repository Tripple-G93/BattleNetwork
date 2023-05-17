// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServices/BNBTServiceTimeRemainingToAttack.h"

#include <BehaviorTree/BlackboardComponent.h>

UBNBTServiceTimeRemainingToAttack::UBNBTServiceTimeRemainingToAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    TimeRemainingToAttackName = "TimeRemainingToAttack";
}

void UBNBTServiceTimeRemainingToAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    float timeRemainingToAttack = OwnerComp.GetBlackboardComponent()->GetValueAsFloat(TimeRemainingToAttackName);
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TimeRemainingToAttackName, timeRemainingToAttack - DeltaSeconds);
}
