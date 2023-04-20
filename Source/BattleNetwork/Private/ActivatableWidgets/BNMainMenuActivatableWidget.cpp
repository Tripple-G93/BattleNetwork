// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNMainMenuActivatableWidget.h"

#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Subsystems/BNSessionSubsystem.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UBNMainMenuActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

    BindButtonWidgets();
}

void UBNMainMenuActivatableWidget::BindButtonWidgets()
{
    if (IsValid(ButtonCreateLocalMultiplayerGame))
    {
        ButtonCreateLocalMultiplayerGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::CreateLocalMultiplayerGame);
    }

    if (IsValid(ButtonFindGame))
    {
        ButtonFindGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::FindSessionWidgetFlow);
    }

    if (IsValid(ButtonCreateSinglePlayerGame))
    {
        ButtonCreateSinglePlayerGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::CreateSinglePlayerGame);
    }

    if (IsValid(ButtonWhatIsNew))
    {
        ButtonWhatIsNew->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::CreateSinglePlayerGame);
    }

    if (IsValid(ButtonCredits))
    {
        ButtonCreateSinglePlayerGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::CreateSinglePlayerGame);
    }
}


void UBNMainMenuActivatableWidget::FindSessionWidgetFlow()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->FindSessions(10, true);
	
    AddWidgetToStack(FindSessionActivatableWidgetClass);
}

void UBNMainMenuActivatableWidget::CreateLocalMultiplayerGame()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->CreateSession(2, true, MultiplayerMapName);

	SetInputModeToGameplay();
}

void UBNMainMenuActivatableWidget::CreateSinglePlayerGame()
{
    UWorld* World = GetWorld();
    if (World)
    {
        UGameplayStatics::OpenLevel(World, "SinglePlayer");
    }

    SetInputModeToGameplay();
}

void UBNMainMenuActivatableWidget::WhatIsNewWidgetFlow()
{
    AddWidgetToStack(WhatIsNewActivatableWidgetClass);
}

void UBNMainMenuActivatableWidget::CreditsWidgetFlow()
{
    AddWidgetToStack(CreditsActivatableWidgetClass);
}

void UBNMainMenuActivatableWidget::AddWidgetToStack(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass)
{
    if (ensure(CommonActivatableWidgetStackReference))
    {
        if (ensure(ActivatableWidgetClass))
        {
            CommonActivatableWidgetStackReference->AddWidget(ActivatableWidgetClass);
        }
    }
}

void UBNMainMenuActivatableWidget::SetInputModeToGameplay() const
{
	const FInputModeGameOnly GameOnlyInputMode;
	GetOwningPlayer()->SetInputMode(GameOnlyInputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);
}