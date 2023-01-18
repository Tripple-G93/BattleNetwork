// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNMainMenuUserWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "UserWidgets/BNCreateSession.h"
#include "UserWidgets/BNFindSessionUserWidget.h"

bool UBNMainMenuUserWidget::Initialize()
{
	const bool bIsInitialized = Super::Initialize();

	FindSessionWidget->SetVisibility(ESlateVisibility::Collapsed);
	FindSessionWidget->GetBackButton()->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::HideFindSessionMenu);
	
	CreateSessionWidget->SetVisibility(ESlateVisibility::Collapsed);
	CreateSessionWidget->GetButtonGoBack()->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::HideCreateGameMenu);
	
	ButtonCreateGame->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::ShowCreateGameMenu);

	ButtonFindGame->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::ShowFindSessionMenu);

	return bIsInitialized;
}

void UBNMainMenuUserWidget::ShowCreateGameMenu()
{
	BorderMainMenu->SetVisibility(ESlateVisibility::Collapsed);
	CreateSessionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBNMainMenuUserWidget::HideCreateGameMenu()
{
	BorderMainMenu->SetVisibility(ESlateVisibility::Visible);
	CreateSessionWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UBNMainMenuUserWidget::ShowFindSessionMenu()
{
	BorderMainMenu->SetVisibility(ESlateVisibility::Collapsed);
	FindSessionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBNMainMenuUserWidget::HideFindSessionMenu()
{
	FindSessionWidget->SetVisibility(ESlateVisibility::Collapsed);
	BorderMainMenu->SetVisibility(ESlateVisibility::Visible);
}
