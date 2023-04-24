// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNFindSessionActivatableWidget.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Subsystems/BNSessionSubsystem.h"

void UBNFindSessionActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!ButtonJoinFirstResult->OnPressed.Contains(this, "JoinFirstSession"))
	{
		ButtonJoinFirstResult->OnPressed.AddDynamic(this, &UBNFindSessionActivatableWidget::JoinFirstSession);
	}
	
	ButtonJoinFirstResult->SetIsEnabled(false);
}

void UBNFindSessionActivatableWidget::JoinFirstSession()
{
	ButtonJoinFirstResult->SetIsEnabled(false);
	SetInputModeToGameplay();
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->JoinGameSession(GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->LastSessionSearch->SearchResults.Top());
}

void UBNFindSessionActivatableWidget::SetInputModeToGameplay() const
{
	const FInputModeGameOnly GameOnlyInputMode;
	GetOwningPlayer()->SetInputMode(GameOnlyInputMode);
	GetOwningPlayer()->SetShowMouseCursor(false);
}

void UBNFindSessionActivatableWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	UBNSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UBNSessionSubsystem>();
	
	if(!ButtonJoinFirstResult->GetIsEnabled() && SessionSubsystem->LastSessionSearch.IsValid() && !SessionSubsystem->LastSessionSearch->SearchResults.IsEmpty())
	{
		ButtonJoinFirstResult->SetIsEnabled(true);
	}
	else if(ButtonJoinFirstResult->GetIsEnabled() && SessionSubsystem->LastSessionSearch.IsValid() && SessionSubsystem->LastSessionSearch->SearchResults.IsEmpty())
	{
		ButtonJoinFirstResult->SetIsEnabled(false);
	}
}
