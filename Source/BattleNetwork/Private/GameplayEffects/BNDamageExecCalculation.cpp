// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayEffects/BNDamageExecCalculation.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "Attributes/BNBaseAttributeSet.h"

struct BNDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(CurrentDamage);

	BNDamageStatics()
	{
		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBNBaseAttributeSet, CurrentDamage, Source, true);
	}
};

static const BNDamageStatics& DamageStatics()
{
	static BNDamageStatics DamageStatics;
	return DamageStatics;
}

UBNDamageExecCalculation::UBNDamageExecCalculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().CurrentDamageDef);
}

void UBNDamageExecCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float Damage = 0.0f;
	// Capture optional damage value set on the damage GE as a CalculationModifier under the ExecutionCalculation
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CurrentDamageDef, EvaluationParameters, Damage);
	// Add SetByCaller damage if it exists
	Damage += FMath::Max<float>(Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), false, -1.0f), 0.0f);

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().CurrentDamageProperty, EGameplayModOp::Additive, Damage));
}
