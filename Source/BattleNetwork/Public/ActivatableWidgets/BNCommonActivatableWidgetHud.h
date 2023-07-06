// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BNCommonActivatableWidgetHud.generated.h"

class UCommonNumericTextBlock;
class UCommonTextBlock;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNCommonActivatableWidgetHud : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> TextCurrentRound;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonNumericTextBlock> NumericTextCurrentRound;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> TextEnemiesRemaining;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonNumericTextBlock> NumericTextEnemiesRemaining;

public:

    void UpdateRoundText(int CurrentRound);

    void UpdateEnemiesRemainingText(int EnemiesRemaining);
};
