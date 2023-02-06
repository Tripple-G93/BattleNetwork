// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNMainMenuUserWidget.h"

#include "Components/Border.h"
#include "Components/Button.h"
#include "Subsystems/BNSessionSubsystem.h"
#include "UserWidgets/BNFindSessionUserWidget.h"

bool UBNMainMenuUserWidget::Initialize()
{
	const bool bIsInitialized = Super::Initialize();

	FindSessionWidget->SetVisibility(ESlateVisibility::Collapsed);
	FindSessionWidget->GetBackButton()->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::HideFindSessionMenu);

	if(IsValid(ButtonCreateLocalMultiplayerGame))
	{
		ButtonCreateLocalMultiplayerGame->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::CreateLocalMultiplayerGame);
	}

	if(IsValid(ButtonFindGame))
	{
		ButtonFindGame->OnPressed.AddDynamic(this, &UBNMainMenuUserWidget::ShowFindSessionMenu);
	}
	
	MultiplayerMapName = "Test";
	
	return bIsInitialized;
}

void UBNMainMenuUserWidget::CreateLocalMultiplayerGame()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->CreateSession(2, true, MultiplayerMapName);
}

void UBNMainMenuUserWidget::ShowFindSessionMenu()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->FindSessions(10, true);
	
	BorderMainMenu->SetVisibility(ESlateVisibility::Collapsed);
	FindSessionWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBNMainMenuUserWidget::HideFindSessionMenu()
{
	FindSessionWidget->SetVisibility(ESlateVisibility::Collapsed);
	BorderMainMenu->SetVisibility(ESlateVisibility::Visible);
}
