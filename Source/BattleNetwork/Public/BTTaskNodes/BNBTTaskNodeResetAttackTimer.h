// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BNBTTaskNodeResetAttackTimer.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBTTaskNodeResetAttackTimer : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditAnywhere, Category="BN|BlackBoardVariables")
    FName TimeRemainingToAttackName;

    UPROPERTY(EditAnywhere, Category = "BN");
    float DefaultTimeRemainingToAttackValue;

public:

    UBNBTTaskNodeResetAttackTimer(const FObjectInitializer& ObjectInitializer);

private:

    EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
