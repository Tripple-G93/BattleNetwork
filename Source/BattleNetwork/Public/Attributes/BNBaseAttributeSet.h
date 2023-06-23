// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include <AbilitySystemComponent.h>
#include "BNBaseAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class ABNEntityPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeathDelegate, ABNEntityPawn*, EntityPawn);

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

protected:

	// Server variable only
	bool bIsPlayerDead;
	
public:

	FOnPlayerDeathDelegate OnPlayerDeathDelegate;
	
	UBNBaseAttributeSet();

	// Current Health, when 0 we expect owner to die unless prevented by an ability. Capped by MaxHealth.
	// Positive changes can directly use this.
	// Negative changes to Health should go through Damage meta attribute.
	UPROPERTY(BlueprintReadOnly, Category = "BN|Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBNBaseAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, Category = "BN|Attributes", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBNBaseAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "BN|Attributes", ReplicatedUsing = OnRep_BulletDamage)
	FGameplayAttributeData BulletDamage;
	ATTRIBUTE_ACCESSORS(UBNBaseAttributeSet, BulletDamage)

	// Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into -Health
	// Temporary value that only exists on the Server. Not replicated.
	UPROPERTY(BlueprintReadOnly, Category = "BN|Attributes")
	FGameplayAttributeData CurrentDamage;
	ATTRIBUTE_ACCESSORS(UBNBaseAttributeSet, CurrentDamage)

	UPROPERTY(BlueprintReadOnly, Category = "BN|Attributes", ReplicatedUsing = OnRep_SpeedPercentRate)
	FGameplayAttributeData SpeedPercentRate;
	ATTRIBUTE_ACCESSORS(UBNBaseAttributeSet, SpeedPercentRate)
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void ResetDeadState();

protected:

	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
	
	/**
	* These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	**/

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_BulletDamage(const FGameplayAttributeData& OldBulletDamage);

	UFUNCTION()
	virtual void OnRep_SpeedPercentRate(const FGameplayAttributeData& OldSpeedPercentRate);

private:

	void EvaluateDamageAttribute(FGameplayEffectContextHandle Context);
	
	bool IsPlayerEntity(AController* SourceController);
};
