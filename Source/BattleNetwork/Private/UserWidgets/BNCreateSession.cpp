// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNCreateSession.h"

#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"

#include "Subsystems/BNSessionSubsystem.h"

UBNCreateSession::UBNCreateSession(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	MultiplayerMapName = "Test";
}

bool UBNCreateSession::Initialize()
{
	const bool bIsInitialized = Super::Initialize();
	
	ButtonCreate->OnPressed.AddDynamic(this, &UBNCreateSession::CreateSession);

	return bIsInitialized;
}

UButton* UBNCreateSession::GetButtonGoBack()
{
	return ButtonGoBack;
}

void UBNCreateSession::CreateSession()
{
	GetGameInstance()->GetSubsystem<UBNSessionSubsystem>()->CreateSession(2, true, MultiplayerMapName);
}
