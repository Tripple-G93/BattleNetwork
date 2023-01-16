// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNMainMenuPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "UserWidgets/BNCreateSession.h"

void ABNMainMenuPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CreateMainMenu();
}

void ABNMainMenuPlayerController::CreateMainMenu()
{
	if(IsLocalPlayerController() && ensure(MainMenuUserWidgetClass) && ensure(!MainMenuUserWidget))
	{
		MainMenuUserWidget = CreateWidget<UBNCreateSession>(this, MainMenuUserWidgetClass);
		MainMenuUserWidget->AddToViewport();
	}
}
