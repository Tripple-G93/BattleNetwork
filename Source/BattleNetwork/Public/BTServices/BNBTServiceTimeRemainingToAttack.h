// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BNBTServiceTimeRemainingToAttack.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBTServiceTimeRemainingToAttack : public UBTService
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditAnywhere, Category = "BN|BlackBoardVariables")
    FName TimeRemainingToAttackName;

public:

    UBNBTServiceTimeRemainingToAttack(const FObjectInitializer& ObjectInitializer);

protected:

    void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
