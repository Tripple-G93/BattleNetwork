// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "BNPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FGSOnGameplayAttributeValueChangedDelegate, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

class UAbilitySystemComponent;
class UBNAbilitySystemComponent;
class UBNBaseAttributeSet;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
protected:

	UPROPERTY()
	UBNAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UBNBaseAttributeSet* BaseAttributeSet;

	// Attribute changed delegate handles
	FDelegateHandle HealthChangedDelegateHandle;


public:

	ABNPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UBNBaseAttributeSet* GetAttributeSetBase() const;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
};
