// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/BNAT_PlayFlipbookAndWaitForEvent.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "PaperFlipbookComponent.h"
#include "Pawns/BNEntityPawn.h"

UBNAT_PlayFlipbookAndWaitForEvent::UBNAT_PlayFlipbookAndWaitForEvent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UBNAT_PlayFlipbookAndWaitForEvent* UBNAT_PlayFlipbookAndWaitForEvent::PlayMontageAndWaitForEvent(
	UGameplayAbility* OwningAbility, FGameplayTagContainer EventTags, FName TaskInstanceName)
{
	UBNAT_PlayFlipbookAndWaitForEvent* MyObj = NewAbilityTask<UBNAT_PlayFlipbookAndWaitForEvent>(OwningAbility, TaskInstanceName);
	MyObj->EventTagContainer = EventTags;

	return MyObj;
}

void UBNAT_PlayFlipbookAndWaitForEvent::Activate()
{
	if(Ability == nullptr)
	{
		return;
	}

	bool bPlayedFlipBookAnimation = false;
	UBNAbilitySystemComponent* BNAbilitySystemComponent = GetTargetASC();

	if(AbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->AvatarActor);
		if(ensure(EntityPawn))
		{
			// Bind to event callback
			EventHandle = BNAbilitySystemComponent->AddGameplayEventTagContainerDelegate(EventTagContainer, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UBNAT_PlayFlipbookAndWaitForEvent::OnGameplayEvent));
			
			CancelledHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UBNAT_PlayFlipbookAndWaitForEvent::OnAbilityCancelled);

			EntityPawn->UpdateAnimation(FGameplayTag::RequestGameplayTag(FName("Entity.Ability.Skill1")));
			UPaperFlipbookComponent* PaperFlipbookComponent = EntityPawn->GetPaperFlipbookComponent();
			PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UBNAT_PlayFlipbookAndWaitForEvent::OnPaperFlipBookAnimationLoopEnded);
			PaperFlipbookComponent->PlayFromStart();
			bPlayedFlipBookAnimation = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UGDAbilityTask_PlayMontageAndWaitForEvent called on invalid AbilitySystemComponent"));
	}

	if (!bPlayedFlipBookAnimation)
	{
		UE_LOG(LogTemp, Warning, TEXT("UGDAbilityTask_PlayMontageAndWaitForEvent called in Ability %s failed to play flipbook animation Task Instance Name %s."), *Ability->GetName(), *InstanceName.ToString());
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			//ABILITY_LOG(Display, TEXT("%s: OnCancelled"), *GetName());
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}

}

void UBNAT_PlayFlipbookAndWaitForEvent::ExternalCancel()
{
	check(AbilitySystemComponent);

	OnAbilityCancelled();

	Super::ExternalCancel();
}

FString UBNAT_PlayFlipbookAndWaitForEvent::GetDebugString() const
{
	return FString::Printf(TEXT("PlayFlipbookAndWaitForEvent."));
}

void UBNAT_PlayFlipbookAndWaitForEvent::OnDestroy(bool AbilityEnded)
{
	if (Ability)
	{
		Ability->OnGameplayAbilityCancelled.Remove(CancelledHandle);
		if(AbilityEnded)
		{
			StopPlayingPaperFlipbook();
		}
	}

	UBNAbilitySystemComponent* GDAbilitySystemComponent = GetTargetASC();
	if (GDAbilitySystemComponent)
	{
		GDAbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTagContainer, EventHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

bool UBNAT_PlayFlipbookAndWaitForEvent::StopPlayingPaperFlipbook()
{
	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (!ActorInfo)
	{
		return false;
	}
	
	ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->AvatarActor);
	if(ensure(EntityPawn))
	{
		EntityPawn->GetPaperFlipbookComponent()->Stop();
		EntityPawn->GetPaperFlipbookComponent()->OnFinishedPlaying.RemoveDynamic(this, &UBNAT_PlayFlipbookAndWaitForEvent::OnPaperFlipBookAnimationLoopEnded);
		EntityPawn->UpdateAnimation(FGameplayTag::RequestGameplayTag(FName("Entity.Idle")));
		EntityPawn->GetPaperFlipbookComponent()->PlayFromStart();
		return true;
	}

	return false;
}

UBNAbilitySystemComponent* UBNAT_PlayFlipbookAndWaitForEvent::GetTargetASC()
{
	return Cast<UBNAbilitySystemComponent>(AbilitySystemComponent);
}

void UBNAT_PlayFlipbookAndWaitForEvent::OnAbilityCancelled()
{
	if(StopPlayingPaperFlipbook())
	{
		// Let the BP handle the interrupt as well
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
		}
	}
}

void UBNAT_PlayFlipbookAndWaitForEvent::OnPaperFlipBookAnimationLoopEnded()
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast(FGameplayTag(), FGameplayEventData());
	}

	EndTask();
}

void UBNAT_PlayFlipbookAndWaitForEvent::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *Payload;
		TempData.EventTag = EventTag;

		EventReceived.Broadcast(EventTag, TempData);
	}
}
