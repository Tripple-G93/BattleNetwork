// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/BNBaseGameplayAbility.h"
#include <GameplayTagContainer.h>
#include "BNGameplayAbilityFireProjectile.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNGameplayAbilityFireProjectile : public UBNBaseGameplayAbility
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditDefaultsOnly, Category="BN")
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;

    UPROPERTY(EditDefaultsOnly, Category="BN")
    FName PaperSpriteSocketName;

    UPROPERTY(EditDefaultsOnly, Category="BN|Gameplay Tags")
    FGameplayTag DefaultTeamComparisonGameplayTag;

    UPROPERTY(EditDefaultsOnly, Category="BN|Gameplay Tags")
    FGameplayTag DamageGameplayTag;

    UPROPERTY(EditDefaultsOnly, Category="BN|Gameplay Tags")
    FGameplayTag ProjectileTypeGameplayTag;

public:

    UBNGameplayAbilityFireProjectile(const FObjectInitializer& ObjectInitializer);

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

    UFUNCTION()
    void OnCompleted(FTransform BulletSpawnLocation);

};
