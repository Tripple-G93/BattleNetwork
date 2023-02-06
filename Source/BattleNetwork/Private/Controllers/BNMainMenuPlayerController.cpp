// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNMainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"

void ABNMainMenuPlayerController::CreateMainMenu()
{
	if(IsLocalPlayerController() && ensure(MainMenuUserWidgetClass) && ensure(!MainMenuUserWidget))
	{
		MainMenuUserWidget = CreateWidget(this, MainMenuUserWidgetClass);
		MainMenuUserWidget->AddToViewport();
	}
}

void ABNMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateMainMenu();
}
