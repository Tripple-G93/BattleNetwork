// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilities/BNGA_FireBullet.h"

#include "PaperFlipbookComponent.h"
#include "AbilityTasks/BNAT_PlayFlipbookAndWaitForEvent.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Pawns/BNEntityPawn.h"

UBNGA_FireBullet::UBNGA_FireBullet()
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
	Task->EventReceived.AddDynamic(this, &UBNGA_FireBullet::EventReceived);
	// ReadyForActivation() is how you activate the AbilityTask in C++. Blueprint has magic from K2Node_LatentGameplayTaskCall that will automatically call ReadyForActivation().
	Task->ReadyForActivation();
	
}

void UBNGA_FireBullet::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}

void UBNGA_FireBullet::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	//TODO BN: Move the stuff fromt the event recieved into this function instead. Oh and remove the event tag as a whole from this class. It is not needed for this situation. 
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UBNGA_FireBullet::EventReceived(FGameplayTag EventTag, FGameplayEventData EventData)
{
	if (GetOwningActorFromActorInfo()->GetLocalRole() == ROLE_Authority)
	{
		ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(GetAvatarActorFromActorInfo());
		if (!EntityPawn)
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}
		
		UPaperFlipbook* PaperFlipbook = EntityPawn->GetPaperFlipbookComponent()->GetFlipbook();
		const int32 NumberOfKeyFrames = PaperFlipbook->GetNumKeyFrames();
		FTransform GunLocation;

		if(!ensure(PaperFlipbook->FindSocket(TEXT("Gun"), NumberOfKeyFrames - 1, GunLocation)))
		{
			EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		}

		// TODO BN: We want to be able to turn on a projectile and pass in the transform as well as a tag that will determine direction of the projectile
	}
}
