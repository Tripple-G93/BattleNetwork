// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/BNGameplayAbilityFireProjectile.h"

#include "AbilityTasks/BNAbilityTaskFireAnimation.h"

UBNGameplayAbilityFireProjectile::UBNGameplayAbilityFireProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UBNGameplayAbilityFireProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (ensure(!AbilityTags.IsEmpty()) && CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        UBNAbilityTaskFireAnimation* abilitytaskFireAnimation = UBNAbilityTaskFireAnimation::PlayFlipBookFireAnimationAndWaitForEvent(this, NAME_None, AbilityTags.First(), PaperSpriteSocketName);
        abilitytaskFireAnimation->OnCompleted.AddDynamic(this, &UBNGameplayAbilityFireProjectile::OnCompleted);
        abilitytaskFireAnimation->OnFireProjectile.AddDynamic(this, &UBNGameplayAbilityFireProjectile::OnFireProjectile);
        abilitytaskFireAnimation->ReadyForActivation();
    }
    else
    {
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
    }
    
}

void UBNGameplayAbilityFireProjectile::OnCompleted(FTransform BulletSpawnLocation)
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBNGameplayAbilityFireProjectile::OnFireProjectile(FTransform BulletSpawnLocation)
{

}