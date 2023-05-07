// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/BNBaseGameplayAbility.h"
#include "BNGameplayAbilityFireProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNGameplayAbilityFireProjectile : public UBNBaseGameplayAbility
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

public:

    UBNGameplayAbilityFireProjectile(const FObjectInitializer& ObjectInitializer);
};
