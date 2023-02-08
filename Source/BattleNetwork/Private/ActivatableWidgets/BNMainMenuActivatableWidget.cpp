// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNMainMenuActivatableWidget.h"

#include "Components/Button.h"
#include "Subsystems/BNSessionSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

bool UBNMainMenuActivatableWidget::Initialize()
{
	const bool bIsInitialized = Super::Initialize();

	if(IsValid(ButtonCreateLocalMultiplayerGame))
	{
		ButtonCreateLocalMultiplayerGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::CreateLocalMultiplayerGame);
	}

	if(IsValid(ButtonFindGame))
	{
		ButtonFindGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::AddFindSessionActivatableWidgetToStack);
	}
	
	MultiplayerMapName = "Test";
	
	return bIsInitialized;
}

void UBNMainMenuActivatableWidget::AddFindSessionActivatableWidgetToStack()
{
	if(ensure(CommonActivatableWidgetStackReference))
	{
		if(ensure(FindSessionActivatableWidgetClass) && !IsValid(FindSessionActivatableWidget))
		{
			FindSessionActivatableWidget = Cast<UBNStackActivatableWidget>(CommonActivatableWidgetStackReference->AddWidget(FindSessionActivatableWidgetClass));
			if(ensure(FindSessionActivatableWidget))
			{
				FindSessionActivatableWidget->SetCommonActivatableWidgetStackReference(CommonActivatableWidgetStackReference);
			}
		}
	}

	/*
	if(!IsValid(FindSessionActivatableWidget) && !FindSessionActivatableWidget->IsActivated())
	{
		FindSessionActivatableWidget->ActivateWidget();
		DeactivateWidget();
	}
	*/
}

void UBNMainMenuActivatableWidget::CreateLocalMultiplayerGame()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->CreateSession(2, true, MultiplayerMapName);
}
