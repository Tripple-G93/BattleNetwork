// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStates/BNPlayerState.h"

#include "ActorComponents/BNAbilitySystemComponent.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNPlayerController.h"

ABNPlayerState::ABNPlayerState()
{
	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UBNAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Mixed mode means we only are replicated the GEs to ourself, not the GEs to simulated proxies. If another GDPlayerState (Hero) receives a GE,
	// we won't be told about it by the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Create the attribute set, this replicates by default
	// Adding it as a subobject of the owning actor of an AbilitySystemComponent
	// automatically registers the AttributeSet with the AbilitySystemComponent
	BaseAttributeSet = CreateDefaultSubobject<UBNBaseAttributeSet>(TEXT("AttributeSetBase"));
	
	// Set PlayerState's NetUpdateFrequency to the same as the Character.
	// Default is very low for PlayerStates and introduces perceived lag in the ability system.
	// 100 is probably way too high for a shipping game, you can adjust to fit your needs.
	NetUpdateFrequency = 100.0f;
}

UAbilitySystemComponent* ABNPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBNBaseAttributeSet* ABNPlayerState::GetAttributeSetBase() const
{
	return BaseAttributeSet;
}

void ABNPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks Example
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &ABNPlayerState::HealthChanged);
	}
}

void ABNPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	/*
	// Check for and handle knockdown and death
	AGSHeroCharacter* Hero = Cast<AGSHeroCharacter>(GetPawn());
	if (IsValid(Hero) && !IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		if (Hero)
		{
			if (!AbilitySystemComponent->HasMatchingGameplayTag(KnockedDownTag))
			{
				Hero->KnockDown();
			}
			else
			{
				Hero->FinishDying();
			}
		}
	}
	*/
}
