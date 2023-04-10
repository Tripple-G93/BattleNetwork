// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BNEnemyAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditDefaultsOnly, Category="BN|BehaviorTree")
    TObjectPtr<UBehaviorTree> BehaviorTree;

    void BeginPlay() override;

};