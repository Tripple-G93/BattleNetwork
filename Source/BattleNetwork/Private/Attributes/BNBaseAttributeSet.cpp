// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/BNBaseAttributeSet.h"

#include "Pawns/BNEntityPawn.h"
#include "Pawns/BNPlayerPawn.h"

#include <GameplayEffect.h>
#include <GameplayEffectExtension.h>
#include <Net/UnrealNetwork.h>

UBNBaseAttributeSet::UBNBaseAttributeSet()
{
	bIsPlayerDead = false;
}

void UBNBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// If a Max value changes, adjust current to keep Current % of Current to Max
	if (Attribute == GetMaxHealthAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UBNBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	FGameplayTagContainer SpecAssetTags;
	Data.EffectSpec.GetAllAssetTags(SpecAssetTags);

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	ABNEntityPawn* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<ABNEntityPawn>(TargetActor);
	}

	// Get the Source actor
	AActor* SourceActor = nullptr;
	AController* SourceController = nullptr;
	ABNEntityPawn* SourceCharacter = nullptr;
	if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
	{
		SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
		SourceController = Source->AbilityActorInfo->PlayerController.Get();
		if (SourceController == nullptr && SourceActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(SourceActor))
			{
				SourceController = Pawn->GetController();
			}
		}

		// Use the controller to find the source pawn
		if (SourceController)
		{
			SourceCharacter = Cast<ABNEntityPawn>(SourceController->GetPawn());
		}
		else
		{
			SourceCharacter = Cast<ABNEntityPawn>(SourceActor);
		}

		// Set the causer actor based on context if it's set
		if (Context.GetEffectCauser())
		{
			SourceActor = Context.GetEffectCauser();
		}
	}

	if (Data.EvaluatedData.Attribute == GetCurrentDamageAttribute())
	{
		EvaluateDamageAttribute(Context);
	}// Damage
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	if(SourceController->GetLocalRole() == ROLE_Authority && GetHealth() <= 0 && IsPlayerEntity(SourceController) && !bIsPlayerDead)
	{
		bIsPlayerDead = true;
		OnPlayerDeathDelegate.Broadcast(TargetCharacter);
	}
}

void UBNBaseAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UBNBaseAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBNBaseAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBNBaseAttributeSet, BulletDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBNBaseAttributeSet, SpeedPercentRate, COND_None, REPNOTIFY_Always);
}

void UBNBaseAttributeSet::ResetDeadState()
{
    bIsPlayerDead = false;
}

void UBNBaseAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute,
	const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UBNBaseAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBNBaseAttributeSet, Health, OldHealth);
}

void UBNBaseAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBNBaseAttributeSet, MaxHealth, OldMaxHealth);
}

void UBNBaseAttributeSet::OnRep_BulletDamage(const FGameplayAttributeData& OldBulletDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBNBaseAttributeSet, BulletDamage, OldBulletDamage);
}

void UBNBaseAttributeSet::OnRep_SpeedPercentRate(const FGameplayAttributeData& OldSpeedPercentRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBNBaseAttributeSet, MaxHealth, SpeedPercentRate);
}

void UBNBaseAttributeSet::EvaluateDamageAttribute(FGameplayEffectContextHandle Context)
{
	// Try to extract a hit result
	FHitResult HitResult;
	if (Context.GetHitResult())
	{
		HitResult = *Context.GetHitResult();
	}
		
	// Store a local copy of the amount of damage done and clear the damage attribute
	const float LocalCurrentDamage = GetCurrentDamage();
	SetCurrentDamage(0.f);
	if (LocalCurrentDamage > 0.0f)
	{
		// Apply the health change and then clamp it
		const float NewHealth = GetHealth() - LocalCurrentDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.0f, GetMaxHealth()));
	}
}

bool UBNBaseAttributeSet::IsPlayerEntity(AController* SourceController)
{
	return SourceController->GetPawn()->IsA(ABNPlayerPawn::StaticClass());
}
