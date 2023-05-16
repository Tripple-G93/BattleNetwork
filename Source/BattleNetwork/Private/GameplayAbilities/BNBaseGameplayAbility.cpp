// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/BNBaseGameplayAbility.h"
#include "AbilitySystemComponent.h"

UBNBaseGameplayAbility::UBNBaseGameplayAbility(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Default to Instance Per Actor
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

	bActivateAbilityOnGranted = false;
}

void UBNBaseGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	if (bActivateAbilityOnGranted)
	{
		bool ActivatedAbility = ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}