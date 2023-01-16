// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameplayEffectTypes.h"
#include "UserWidgets/BNWorldSpaceToWidgetUserWidget.h"

#include "BNEntityUserWidget.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNEntityUserWidget : public UBNWorldSpaceToWidgetUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	float CachedMaxHealth;

public:

	void InitializeWidgetWithAttributes();

	void InitializeAttributeBindingsToWidget();

protected:
	
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
};
