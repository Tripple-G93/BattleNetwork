// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNCreateSession.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Kismet/GameplayStatics.h"

#include "Subsystems/BNSessionSubsystem.h"

UBNCreateSession::UBNCreateSession(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	MapName = "Test";
}

bool UBNCreateSession::Initialize()
{
	const bool bIsInitialized = Super::Initialize();
	
	ButtonCreate->OnPressed.AddDynamic(this, &UBNCreateSession::CreateSession);

	return bIsInitialized;
}

void UBNCreateSession::CreateSession()
{
	const int32 NumberOfPlayers = static_cast<int32>(SliderNumberPlayers->GetValue());
	const bool IsLocalNetworkEnabled = CheckBoxEnableLocalNetwork->IsChecked();
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->CreateSession(NumberOfPlayers, IsLocalNetworkEnabled, MapName);

	UGameplayStatics::OpenLevel(GetWorld(), MapName);
}
