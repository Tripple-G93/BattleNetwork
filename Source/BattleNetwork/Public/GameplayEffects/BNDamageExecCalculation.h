// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BNDamageExecCalculation.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNDamageExecCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UBNDamageExecCalculation();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
