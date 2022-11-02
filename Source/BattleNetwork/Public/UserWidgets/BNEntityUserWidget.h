// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UserWidgets/BNWorldSpaceToWidgetUserWidget.h"
#include "BNEntityUserWidget.generated.h"

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
	
};
