// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/BNGameplayAbilityFireProjectile.h"

UBNGameplayAbilityFireProjectile::UBNGameplayAbilityFireProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UBNGameplayAbilityFireProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{

}

void UBNGameplayAbilityFireProjectile::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData, FTransform BulletSpawnLocation)
{

}
