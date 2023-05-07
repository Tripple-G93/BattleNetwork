// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilities/BNBaseGameplayAbility.h"
#include "BNGA_FireBullet.generated.h"

UCLASS()
class BATTLENETWORK_API UBNGA_FireBullet : public UBNBaseGameplayAbility
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<UGameplayEffect> DamageGameplayEffect;
	
public:

	UBNGA_FireBullet(const FObjectInitializer& ObjectInitializer);
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UFUNCTION()
	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData, FTransform BulletSpawnLocation);

	UFUNCTION()
	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData, FTransform BulletSpawnLocation);
	
};
