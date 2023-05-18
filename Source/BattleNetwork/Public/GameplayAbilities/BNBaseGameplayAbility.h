// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BattleNetwork/BattleNetwork.h"
#include "BNBaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBNBaseGameplayAbility(const FObjectInitializer& ObjectInitializerconst);

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BN|Ability")
	EGSAbilityInputID AbilityInputID = EGSAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BN|Ability")
	EGSAbilityInputID AbilityID = EGSAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilites forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|Ability")
	bool bActivateAbilityOnGranted;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

};
