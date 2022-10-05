// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BNAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	bool bCharacterAbilitiesGiven = false;
	bool bStartupEffectsApplied = false;

protected:

public:

	UBNAbilitySystemComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual bool GetShouldTick() const override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;

	virtual void NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled) override;

	// Version of function in AbilitySystemGlobals that returns correct type
	static UBNAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

	// Input bound to an ability is pressed
	virtual void AbilityLocalInputPressed(int32 InputID) override;

	// Exposes GetTagCount to Blueprint
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities", Meta = (DisplayName = "GetTagCount", ScriptName = "GetTagCount"))
	int32 K2_GetTagCount(FGameplayTag TagToCheck) const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Abilities")
	FGameplayAbilitySpecHandle FindAbilitySpecHandleForClass(TSubclassOf<UGameplayAbility> AbilityClass, UObject* OptionalSourceObject=nullptr);

	// Turn on RPC batching in ASC. Off by default.
	virtual bool ShouldDoServerAbilityRPCBatch() const override { return true; }

	// Exposes AddLooseGameplayTag to Blueprint. This tag is *not* replicated.
	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "AddLooseGameplayTag"))
	void K2_AddLooseGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);

	// Exposes AddLooseGameplayTags to Blueprint. These tags are *not* replicated.
	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "AddLooseGameplayTags"))
	void K2_AddLooseGameplayTags(const FGameplayTagContainer& GameplayTags, int32 Count = 1);

	// Exposes RemoveLooseGameplayTag to Blueprint. This tag is *not* replicated.
	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "RemoveLooseGameplayTag"))
	void K2_RemoveLooseGameplayTag(const FGameplayTag& GameplayTag, int32 Count = 1);

	// Exposes RemoveLooseGameplayTags to Blueprint. These tags are *not* replicated.
	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "RemoveLooseGameplayTags"))
	void K2_RemoveLooseGameplayTags(const FGameplayTagContainer& GameplayTags, int32 Count = 1);

	// Attempts to activate the given ability handle and batch all RPCs into one. This will only batch all RPCs that happen
	// in one frame. Best case scenario we batch ActivateAbility, SendTargetData, and EndAbility into one RPC instead of three.
	// Worst case we batch ActivateAbility and SendTargetData into one RPC instead of two and call EndAbility later in a separate
	// RPC. If we can't batch SendTargetData or EndAbility with ActivateAbility because they don't happen in the same frame due to
	// latent ability tasks for example, then batching doesn't help and we should just activate normally.
	// Single shots (semi auto fire) combine ActivateAbility, SendTargetData, and EndAbility into one RPC instead of three.
	// Full auto shots combine ActivateAbility and SendTargetData into one RPC instead of two for the first bullet. Each subsequent
	// bullet is one RPC for SendTargetData. We then send one final RPC for the EndAbility when we're done firing.
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual bool BatchRPCTryActivateAbility(FGameplayAbilitySpecHandle InAbilityHandle, bool EndAbilityImmediately);

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void ExecuteGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void AddGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	UFUNCTION(BlueprintCallable, Category = "GameplayCue", Meta = (AutoCreateRefTerm = "GameplayCueParameters", GameplayTagFilter = "GameplayCue"))
	void RemoveGameplayCueLocal(const FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual FString GetCurrentPredictionKeyStatus();

	/**
	* If this ASC has a valid prediction key, attempt to predictively apply this GE. Used in Pre/PostInteract() on the Interacter's ASC.
	* If the key is not valid, it will apply the GE without prediction.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameplayEffects", Meta = (DisplayName = "ApplyGameplayEffectToSelfWithPrediction"))
	FActiveGameplayEffectHandle BP_ApplyGameplayEffectToSelfWithPrediction(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle EffectContext);

	/**
	* If this ASC has a valid prediction key, attempt to predictively apply this GE to the target. Used in Pre/PostInteract() on the Interacter's ASC.
	* If the key is not valid, it will apply the GE to the target without prediction.
	*/
	UFUNCTION(BlueprintCallable, Category = "GameplayEffects", Meta = (DisplayName = "ApplyGameplayEffectToTargetWithPrediction"))
	FActiveGameplayEffectHandle BP_ApplyGameplayEffectToTargetWithPrediction(TSubclassOf<UGameplayEffect> GameplayEffectClass, UAbilitySystemComponent* Target, float Level, FGameplayEffectContextHandle Context);

protected:
};
