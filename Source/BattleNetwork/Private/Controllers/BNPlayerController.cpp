// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BNPlayerController.h"

#include "ActorComponents/BNAbilitySystemComponent.h"
#include "ActivatableWidgets/BNGameResultActivatableWidget.h"
#include "PlayerStates/BNPlayerState.h"

#include <CommonActivatableWidget.h>

void ABNPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ABNPlayerState* PS = GetPlayerState<ABNPlayerState>();
	if (PS)
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
	
}

// Client Implementation
void ABNPlayerController::DisplayWinResultUI_Implementation()
{
	CreateResultWidget(WinResultText);
}

// Client Implementation
void ABNPlayerController::DisplayLossResultUI_Implementation()
{
	CreateResultWidget(LossResultText);
}

void ABNPlayerController::SetInputModeUI()
{
	const FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);
	SetShowMouseCursor(true);
}

void ABNPlayerController::CreateResultWidget(FText Text)
{
	SetInputModeUI();
	
	if(IsLocalPlayerController() && ensure(ResultActivatableWidgetClass) && ensure(!ResultActivatableWidget))
	{
		ResultActivatableWidget = CreateWidget<UBNGameResultActivatableWidget>(this, ResultActivatableWidgetClass);
		ResultActivatableWidget->SetResultTextBlock(Text);
		ResultActivatableWidget->AddToViewport();
		ResultActivatableWidget->ActivateWidget();
	}
}
