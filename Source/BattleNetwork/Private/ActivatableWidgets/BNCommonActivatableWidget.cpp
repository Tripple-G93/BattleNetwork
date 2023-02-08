// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNCommonActivatableWidget.h"

#include "Components/Button.h"
#include "Subsystems/BNSessionSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

bool UBNCommonActivatableWidget::Initialize()
{
	const bool bIsInitialized = Super::Initialize();

	if(IsValid(ButtonCreateLocalMultiplayerGame))
	{
		ButtonCreateLocalMultiplayerGame->OnPressed.AddDynamic(this, &UBNCommonActivatableWidget::CreateLocalMultiplayerGame);
	}

	if(IsValid(ButtonFindGame))
	{
		ButtonFindGame->OnPressed.AddDynamic(this, &UBNCommonActivatableWidget::AddFindSessionActivatableWidgetToStack);
	}
	
	MultiplayerMapName = "Test";
	
	return bIsInitialized;
}

void UBNCommonActivatableWidget::AddFindSessionActivatableWidgetToStack()
{
	if(ensure(FindSessionActivatableWidgetClass) && !IsValid(FindSessionActivatableWidget))
	{
		FindSessionActivatableWidget = CommonActivatableWidgetStack->AddWidget(FindSessionActivatableWidgetClass);
	}
}

void UBNCommonActivatableWidget::CreateLocalMultiplayerGame()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->CreateSession(2, true, MultiplayerMapName);
}
