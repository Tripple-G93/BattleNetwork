// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNMainMenuActivatableWidget.h"

#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
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

    if (IsValid(ButtonCreateSinglePlayerGame))
    {
        ButtonCreateSinglePlayerGame->OnPressed.AddDynamic(this, &UBNMainMenuActivatableWidget::CreateSinglePlayerGame);
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

void UBNMainMenuActivatableWidget::CreateSinglePlayerGame()
{
    UWorld* World = GetWorld();
    if (World)
    {
        // This is a blocking call, but since we're in a menu we can do that.
        // If we were in game we'd have to do this differently.
        UGameplayStatics::OpenLevel(World, "SinglePlayer");
    }

    SetInputModeToGameplay();
}

void UBNMainMenuActivatableWidget::SetInputModeToGameplay() const
{
	const FInputModeGameOnly GameOnlyInputMode;
	GetOwningPlayer()->SetInputMode(GameOnlyInputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);
}
