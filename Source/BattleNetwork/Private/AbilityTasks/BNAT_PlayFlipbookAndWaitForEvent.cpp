// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/BNAT_PlayFlipbookAndWaitForEvent.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Pawns/BNEntityPawn.h"

UBNAT_PlayFlipbookAndWaitForEvent::UBNAT_PlayFlipbookAndWaitForEvent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bStopWhenAbilityEnds = true;

	
}

UBNAT_PlayFlipbookAndWaitForEvent* UBNAT_PlayFlipbookAndWaitForEvent::PlayMontageAndWaitForEvent(
	UGameplayAbility* OwningAbility, FName TaskInstanceName, UPaperFlipbook* PaperFlipBookAnimation,
	FGameplayTagContainer EventTags, float PlayRate, bool bStopWhenAbilityEnd)
{
	UBNAT_PlayFlipbookAndWaitForEvent* MyObj = NewAbilityTask<UBNAT_PlayFlipbookAndWaitForEvent>(OwningAbility, TaskInstanceName);
	MyObj->PaperFlipbookToPlay = PaperFlipBookAnimation;
	MyObj->EventTagContainer = EventTags;
	MyObj->PaperFlipBookPlayRate = PlayRate;
	MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnd;

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
		ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->OwnerActor);
		if(ensure(EntityPawn))
		{
			
		}
		// Get the animation
		// If the animation is valid
			// Create the cancel binding
			// Get the paper flip book component
			// Bind to event call back
			// Set the paper flip book animation
			// Set the loop to false (Done in the table)
			// Bind to filpbookanimation ended function
			// Set the played montage to true
	}
}

void UBNAT_PlayFlipbookAndWaitForEvent::ExternalCancel()
{
	check(AbilitySystemComponent);

	OnAbilityCancelled();

	Super::ExternalCancel();
}

UBNAbilitySystemComponent* UBNAT_PlayFlipbookAndWaitForEvent::GetTargetASC()
{
	return Cast<UBNAbilitySystemComponent>(AbilitySystemComponent);
}

void UBNAT_PlayFlipbookAndWaitForEvent::OnAbilityCancelled()
{
	// TODO BN: Conditional statement to stop playing the paper flip book animation
	
	// Let the BP handle the interrupt as well
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCancelled.Broadcast(FGameplayTag(), FGameplayEventData());
	}
}

void UBNAT_PlayFlipbookAndWaitForEvent::OnPaperFlipBookAnimationLoopEnded(bool bInterrupted)
{
	if (!bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCompleted.Broadcast(FGameplayTag(), FGameplayEventData());
		}
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
