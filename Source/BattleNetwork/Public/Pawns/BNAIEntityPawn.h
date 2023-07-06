// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BNEntityPawn.h"
#include "BNAIEntityPawn.generated.h"

class UBNAbilitySystemComponent;
class UBNBaseAttributeSet;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNAIEntityPawn : public ABNEntityPawn
{
	GENERATED_BODY()
	
protected:

    UPROPERTY()
    UBNAbilitySystemComponent* HardRefenceAbilitySystemComponent;

    UPROPERTY()
    UBNBaseAttributeSet* HardRefenceBaseAttributeSet;

public:

    ABNAIEntityPawn(const FObjectInitializer& ObjectInitializer);

    void StartBehaviorTree();

    void StopBehaviorTree();

    virtual void EntityDied() override;
protected:

    virtual void BeginPlay() override;
};
