// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNFindSessionUserWidget.h"

#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Subsystems/BNSessionSubsystem.h"

#include "Kismet/GameplayStatics.h"

bool UBNFindSessionUserWidget::Initialize()
{
	bool bIsInitialized = Super::Initialize();

	ButtonFindSession->OnPressed.AddDynamic(this, &UBNFindSessionUserWidget::FindSession);
	ButtonJoinFirstResult->OnPressed.AddDynamic(this, &UBNFindSessionUserWidget::UBNFindSessionUserWidget::JoinFirstSession);

	return bIsInitialized;
}

UButton* UBNFindSessionUserWidget::GetBackButton()
{
	return ButtonBack;
}

void UBNFindSessionUserWidget::FindSession()
{
	bool bIsLanQuery = CheckBoxEnableNetworkSession->IsChecked();
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->FindSessions(10, bIsLanQuery);
}

void UBNFindSessionUserWidget::JoinFirstSession()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->JoinGameSession(GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->LastSessionSearch->SearchResults.Top());
	//UGameplayStatics::OpenLevel(GetWorld(), "Test");

	
}
