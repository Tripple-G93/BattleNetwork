// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNMainMenuPlayerController.h"

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

void ABNMainMenuPlayerController::SetInputModeUI()
{
	const FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);
}

void ABNMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputModeUI();
	
	CreateMainMenu();
}
