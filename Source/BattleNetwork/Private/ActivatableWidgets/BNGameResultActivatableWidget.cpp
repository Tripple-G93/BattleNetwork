// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNGameResultActivatableWidget.h"

#include "CommonTextBlock.h"

void UBNGameResultActivatableWidget::SetResultTextBlock(FText Text)
{
	ResultTextBlock->SetText(Text);
}

void UBNGameResultActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Do Button binding here to and figure out how to exit the game and go to the main menu
}
