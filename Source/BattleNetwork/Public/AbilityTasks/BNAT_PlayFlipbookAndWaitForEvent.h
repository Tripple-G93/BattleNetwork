// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "BNAT_PlayFlipbookAndWaitForEvent.generated.h"

class UBNAbilitySystemComponent;
class UPaperFlipbook;

/** Delegate type used, EventTag and Payload may be empty if it came from the montage callbacks */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBNPlayFlipbookAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNAT_PlayFlipbookAndWaitForEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	
	/** The montage completely finished playing */
	UPROPERTY(BlueprintAssignable)
	FBNPlayFlipbookAndWaitForEventDelegate OnCompleted;

	/** The montage was interrupted */
	UPROPERTY(BlueprintAssignable)
	FBNPlayFlipbookAndWaitForEventDelegate OnInterrupted;
	
	/** The ability task was explicitly cancelled by another ability */
	UPROPERTY(BlueprintAssignable)
	FBNPlayFlipbookAndWaitForEventDelegate OnCancelled;

	/** One of the triggering gameplay events happened */
	UPROPERTY(BlueprintAssignable)
	FBNPlayFlipbookAndWaitForEventDelegate EventReceived;
	
private:
	

	/** Montage that is playing */
	UPROPERTY()
	UPaperFlipbook* PaperFlipbookToPlay;

	/** List of tags to match against gameplay events */
	UPROPERTY()
	FGameplayTagContainer EventTagContainer;

	/** Playback rate */
	UPROPERTY()
	float PaperFlipBookPlayRate;

	/** Should Flipbook be aborted if ability ends */
	UPROPERTY()
	bool bStopWhenAbilityEnds;

private:

	

public:

	UBNAT_PlayFlipbookAndWaitForEvent(const FObjectInitializer& ObjectInitializer);
	
	/**
	 * Play a montage and wait for it end. If a gameplay event happens that matches EventTags (or EventTags is empty), the EventReceived delegate will fire with a tag and event data.
	 * If StopWhenAbilityEnds is true, this montage will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled.
	 * On normal execution, OnBlendOut is called when the montage is blending out, and OnCompleted when it is completely done playing
	 * OnInterrupted is called if another montage overwrites this, and OnCancelled is called if the ability or task is cancelled
	 *
	 * @param TaskInstanceName Set to override the name of this task, for later querying
	 * @param PaperFlipBookAnimation The Paperflipbook animation to play on the character
	 * @param EventTags Any gameplay events matching this tag will activate the EventReceived callback. If empty, all events will trigger callback
	 * @param PlayRate Change to play the fire animation faster
	 * @param bStopWhenAbilityEnds If true, this paperflipbook will be aborted if the ability ends normally. It is always stopped when the ability is explicitly cancelled
	 */
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UBNAT_PlayFlipbookAndWaitForEvent* PlayMontageAndWaitForEvent(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName,
			UPaperFlipbook* PaperFlipBookAnimation,
			FGameplayTagContainer EventTags,
			float PlayRate = 1.f,
			bool bStopWhenAbilityEnd = true);

	/**
	* The Blueprint node for this task, PlayMontageAndWaitForEvent, has some black magic from the plugin that automagically calls Activate()
	* inside of K2Node_LatentAbilityCall as stated in the AbilityTask.h. Ability logic written in C++ probably needs to call Activate() itself manually.
	*/
	virtual void Activate() override;
	virtual void ExternalCancel() override;
	
private:

	/** Returns our ability system component */
	UBNAbilitySystemComponent* GetTargetASC();

	void OnAbilityCancelled();
	void OnPaperFlipBookAnimationLoopEnded(bool bInterrupted);
	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);
};
