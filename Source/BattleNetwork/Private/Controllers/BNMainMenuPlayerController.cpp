// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNMainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "CommonActivatableWidget.h"

void ABNMainMenuPlayerController::CreateMainMenu()
{
	if(IsLocalPlayerController() && ensure(MainMenuUserWidgetClass) && ensure(!MainMenuUserWidget))
	{
		MainMenuUserWidget = Cast<UCommonActivatableWidget>(CreateWidget(this, MainMenuUserWidgetClass));
		MainMenuUserWidget->AddToViewport();
		MainMenuUserWidget->ActivateWidget();
	}
}

void ABNMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);
	
	CreateMainMenu();
}
