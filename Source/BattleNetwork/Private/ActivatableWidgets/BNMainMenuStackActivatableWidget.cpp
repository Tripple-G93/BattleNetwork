// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNMainMenuStackActivatableWidget.h"

#include "ActivatableWidgets/BNStackActivatableWidget.h"

#include <Widgets/CommonActivatableWidgetContainer.h>

void UBNMainMenuStackActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(ensure(MainMenuActivatableWidgetClass))
	{
		UBNStackActivatableWidget* MainMenuActivatableWidget = Cast<UBNStackActivatableWidget>(MainMenuWidgetStack->AddWidget(MainMenuActivatableWidgetClass));
		
		if(ensure(MainMenuActivatableWidget))
		{
			MainMenuActivatableWidget->SetCommonActivatableWidgetStackReference(MainMenuWidgetStack);
		}
	}
}
