// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BNBTDecoratorCanMove.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBTDecoratorCanMove : public UBTDecorator
{
	GENERATED_BODY()


protected:

    bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
