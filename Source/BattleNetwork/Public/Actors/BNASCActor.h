// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <AbilitySystemInterface.h>
#include "BNASCActor.generated.h"

class UBNAbilitySystemComponent;

UCLASS()
class BATTLENETWORK_API ABNASCActor : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	UBNAbilitySystemComponent* AbilitySystemComponent;
	
public:	
	// Sets default values for this actor's properties
	ABNASCActor();
	
	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
