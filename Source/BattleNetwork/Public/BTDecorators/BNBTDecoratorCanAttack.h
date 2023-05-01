// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BNBTDecoratorCanAttack.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBTDecoratorCanAttack : public UBTDecorator
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditAnywhere, Category="BN|BlackBoardVariables")
    FName TimeRemainingToAttackName;


    bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:

    UBNBTDecoratorCanAttack(const FObjectInitializer& ObjectInitializer);
};
