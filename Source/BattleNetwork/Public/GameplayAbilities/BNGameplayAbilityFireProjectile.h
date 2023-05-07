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

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

    UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData, FTransform BulletSpawnLocation);
};
