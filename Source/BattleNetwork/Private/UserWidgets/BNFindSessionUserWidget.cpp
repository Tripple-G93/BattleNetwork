// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNFindSessionUserWidget.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Subsystems/BNSessionSubsystem.h"

bool UBNFindSessionUserWidget::Initialize()
{
	bool bIsInitialized = Super::Initialize();
	
	ButtonJoinFirstResult->OnPressed.AddDynamic(this, &UBNFindSessionUserWidget::UBNFindSessionUserWidget::JoinFirstSession);

	ButtonJoinFirstResult->SetIsEnabled(false);
	
	return bIsInitialized;
}

UButton* UBNFindSessionUserWidget::GetBackButton()
{
	return ButtonBack;
}

void UBNFindSessionUserWidget::JoinFirstSession()
{
	ButtonJoinFirstResult->SetIsEnabled(false);
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->JoinGameSession(GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->LastSessionSearch->SearchResults.Top());
}

void UBNFindSessionUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
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
