// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNEntityUserWidget.h"

#include "Attributes/BNBaseAttributeSet.h"
#include "Pawns/BNEntityPawn.h"

#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>

void UBNEntityUserWidget::InitializeWidgetWithAttributes()
{
	if(ensure(AttachedActor))
	{
		const ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(AttachedActor);
		if(ensure(EntityPawn))
		{
			const UBNBaseAttributeSet* BaseAttributeSet = EntityPawn->GetBaseAttributeSet();
			const float CurrentHealth = BaseAttributeSet->GetHealth();
			HealthText->SetText(FText::AsNumber(CurrentHealth));

			CachedMaxHealth = BaseAttributeSet->GetMaxHealth();
			HealthProgressBar->SetPercent(CurrentHealth / CachedMaxHealth);
		}
	}
}

void UBNEntityUserWidget::InitializeAttributeBindingsToWidget()
{
	if(ensure(AttachedActor))
	{
		const ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(AttachedActor);
		if(ensure(EntityPawn))
		{
			const UBNBaseAttributeSet* BaseAttributeSet = EntityPawn->GetBaseAttributeSet();
			UAbilitySystemComponent* AbilitySystemComponent = EntityPawn->GetAbilitySystemComponent();

			AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
				BaseAttributeSet->GetHealthAttribute()).AddUObject(this, &UBNEntityUserWidget::HealthChanged);
		}
	}
}

void UBNEntityUserWidget::HealthChanged(const FOnAttributeChangeData& Data)
{
	const float CurrentHealth = Data.NewValue;
	HealthText->SetText(FText::AsNumber(CurrentHealth));
	HealthProgressBar->SetPercent(CurrentHealth / CachedMaxHealth);
}
