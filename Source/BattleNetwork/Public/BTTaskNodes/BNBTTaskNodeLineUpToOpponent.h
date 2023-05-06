// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BNBTTaskNodeLineUpToOpponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBTTaskNodeLineUpToOpponent : public UBTTaskNode
{
	GENERATED_BODY()
	
   EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
