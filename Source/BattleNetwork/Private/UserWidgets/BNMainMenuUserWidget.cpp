// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNMainMenuUserWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "UserWidgets/BNCreateSession.h"

bool UBNMainMenuUserWidget::Initialize()
{
	const bool bIsInitialized = Super::Initialize();

	CreateSessionWidget->SetVisibility(ESlateVisibility::Collapsed);
	ButtonCreateGame->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::ShowCreateGameMenu);

	return bIsInitialized;
}

void UBNMainMenuUserWidget::ShowCreateGameMenu()
{
	BorderMainMenu->SetVisibility(ESlateVisibility::Collapsed);
	CreateSessionWidget->SetVisibility(ESlateVisibility::Visible);
	
}
