// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNCommonActivatableWidgetHud.h"

#include <CommonNumericTextBlock.h>

void UBNCommonActivatableWidgetHud::UpdateRoundText(int CurrentRound)
{
    NumericTextCurrentRound->SetCurrentValue(CurrentRound);
}

void UBNCommonActivatableWidgetHud::UpdateEnemiesRemainingText(int EnemiesRemaining)
{
    NumericTextEnemiesRemaining->SetCurrentValue(EnemiesRemaining);
}
