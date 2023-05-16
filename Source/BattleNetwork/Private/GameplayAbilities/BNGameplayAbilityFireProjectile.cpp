// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/BNGameplayAbilityFireProjectile.h"

#include "AbilityTasks/BNAbilityTaskFireAnimation.h"
#include "Actors/BNProjectilePool.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "GameModes/BNGameModeInitial.h"
#include "PaperFlipbookComponent.h"
#include "Pawns/BNEntityPawn.h"

#include <GameplayEffectTypes.h>

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

void UBNGameplayAbilityFireProjectile::OnCompleted()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBNGameplayAbilityFireProjectile::OnFireProjectile(FTransform BulletSpawnLocation)
{
    if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority)
    {
        ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(CurrentActorInfo->AvatarActor);
        if (ensure(EntityPawn))
        {
            FVector SpawnLocation = BulletSpawnLocation.GetLocation();

            const float BulletDamage = EntityPawn->GetBaseAttributeSet()->GetBulletDamage();

            FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());
            GameplayEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(DamageGameplayTag, BulletDamage);

            ABNGameModeInitial* GameModeBase = Cast<ABNGameModeInitial>(GetWorld()->GetAuthGameMode());
            GameModeBase->GetBulletProjectilePool()->CreateProjectile(ProjectileTypeGameplayTag, SpawnLocation, EntityPawn->GetTeamTag(), GameplayEffectSpecHandle);
        }
    }
}
