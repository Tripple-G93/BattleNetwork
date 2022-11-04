// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "Tables/BNFlipbookAnimationTable.h"
#include "BattleNetwork/BattleNetwork.h"
#include "BNBasePawn.generated.h"

class UAbilitySystemComponent;
class UBNAbilitySystemComponent;
class UBNBaseAttributeSet;
class UBNBaseGameplayAbility;
class UGameplayEffect;

UCLASS()
class BATTLENETWORK_API ABNBasePawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<UBNBaseGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartupEffects;

	// Reference to the ASC. It will live on the PlayerState or here if the character doesn't have a PlayerState.
	UPROPERTY()
	UBNAbilitySystemComponent* AbilitySystemComponent;

	// Reference to the AttributeSetBase. It will live on the PlayerState or here if the character doesn't have a PlayerState.
	UPROPERTY()
	UBNBaseAttributeSet* AttributeSetBase; 
	
	TObjectPtr<FBNFlipbookAnimationTableInfoRow> CurrentFlipbookAnimationTableInfoRow;
	
public:

	ABNBasePawn(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UBNBaseAttributeSet* GetBaseAttributeSet() const; 

	// Switch on AbilityID to return individual ability levels.
	UFUNCTION(BlueprintCallable, Category = "GAS|GSCharacter")
	virtual int32 GetAbilityLevel(EGSAbilityInputID AbilityID) const;

	// Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	virtual void RemoveCharacterAbilities();

	/**
	* Getters for attributes from GSAttributeSetBase
	**/

	UFUNCTION(BlueprintCallable, Category = "GASShooter|GSCharacter|Attributes")
	int32 GetCharacterLevel() const;

	UFUNCTION(BlueprintCallable, Category = "GASShooter|GSCharacter|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GASShooter|GSCharacter|Attributes")
	float GetMaxHealth() const;

protected:

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. Must run on Server but we run it on Client too
	// so that we don't have to wait. The Server's replication to the Client won't matter since
	// the values should be the same.
	virtual void InitializeAttributes();
	
	virtual void AddStartupEffects();

	void InitializePlayerGameplayAbilitySystem();
	
};
