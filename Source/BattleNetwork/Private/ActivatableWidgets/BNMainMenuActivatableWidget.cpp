// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNMainMenuActivatableWidget.h"

#include "Components/Button.h"
#include "Subsystems/BNSessionSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UBNMainMenuActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(IsValid(ButtonCreateLocalMultiplayerGame))
	{
		ButtonCreateLocalMultiplayerGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::CreateLocalMultiplayerGame);
	}

	if(IsValid(ButtonFindGame))
	{
		ButtonFindGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::FindSessionWidgetFlow);
	}
}

void UBNMainMenuActivatableWidget::FindSessionWidgetFlow()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->FindSessions(10, true);
	
	if(ensure(CommonActivatableWidgetStackReference))
	{
		if(ensure(FindSessionActivatableWidgetClass))
		{
			CommonActivatableWidgetStackReference->AddWidget(FindSessionActivatableWidgetClass);
		}
	}
}

void UBNMainMenuActivatableWidget::CreateLocalMultiplayerGame()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->CreateSession(2, true, MultiplayerMapName);

	SetInputModeToGameplay();
}

void UBNMainMenuActivatableWidget::SetInputModeToGameplay() const
{
	const FInputModeGameOnly GameOnlyInputMode;
	GetOwningPlayer()->SetInputMode(GameOnlyInputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);
}
