// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BNPlayerState.generated.h"

class UAbilitySystemComponent;
class UBNAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UBNAbilitySystemComponent* AbilitySystemComponent;

public:

	ABNPlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
