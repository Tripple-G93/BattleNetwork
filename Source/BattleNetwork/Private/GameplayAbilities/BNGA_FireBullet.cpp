// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/BNGA_FireBullet.h"

#include "Attributes/BNBaseAttributeSet.h"
#include "AbilityTasks/BNAT_PlayFlipbookAndWaitForEvent.h"
#include "Actors/BNProjectilePool.h"
#include "GameModes/BNGameModeInitial.h"
#include "PaperFlipbookComponent.h"
#include "Pawns/BNEntityPawn.h"

UBNGA_FireBullet::UBNGA_FireBullet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    FGameplayTag Skill1Tag = FGameplayTag::RequestGameplayTag(FName("Entity.Ability.Skill1"));
    AbilityTags.AddTag(Skill1Tag);
    ActivationOwnedTags.AddTag(Skill1Tag);

    ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Entity.Ability")));
    ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Entity.Move")));
}

void UBNGA_FireBullet::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	// Play fire montage and wait for event telling us to spawn the projectile
	UBNAT_PlayFlipbookAndWaitForEvent* Task = UBNAT_PlayFlipbookAndWaitForEvent::PlayMontageAndWaitForEvent(this, FGameplayTagContainer(), NAME_None);
	Task->OnCompleted.AddDynamic(this, &UBNGA_FireBullet::OnCompleted);
	Task->OnInterrupted.AddDynamic(this, &UBNGA_FireBullet::OnCancelled);
	Task->OnCancelled.AddDynamic(this, &UBNGA_FireBullet::OnCancelled);
	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	Task->ReadyForActivation();
	
}

void UBNGA_FireBullet::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData, FTransform BulletSpawnLocation)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UBNGA_FireBullet::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData, FTransform BulletSpawnLocation)
{
	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority)
	{
        // TODO: Delete this class since it is no longer needed
        /*
		ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(CurrentActorInfo->AvatarActor);
		if(ensure(EntityPawn))
		{
			const FVector FlipBookLocation = EntityPawn->GetPaperFlipbookComponent()->GetComponentLocation();
			float SpawnLocationX = FlipBookLocation.X;
			if(EntityPawn->GetTeamTag() == FGameplayTag::RequestGameplayTag("Team1"))
			{
				SpawnLocationX += BulletSpawnLocation.GetLocation().X;
			}
			else
			{
				SpawnLocationX -= BulletSpawnLocation.GetLocation().X;
			}
			
			const FVector SpawnLocation(SpawnLocationX, FlipBookLocation.Y, BulletSpawnLocation.GetLocation().Z + FlipBookLocation.Z);
			
			const float BulletDamage = EntityPawn->GetBaseAttributeSet()->GetBulletDamage();

			ensure(DamageGameplayEffect);
			FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());
			GameplayEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), BulletDamage);
			
			ABNGameModeInitial* GameModeBase = Cast<ABNGameModeInitial>(GetWorld()->GetAuthGameMode());
			GameModeBase->GetBulletProjectilePool()->CreateProjectile(SpawnLocation, EntityPawn->GetTeamTag(), GameplayEffectSpecHandle);
            */
		//}
	}
	
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}