// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNGameResultActivatableWidget.h"

#include "CommonTextBlock.h"
#include "Components/Button.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/BNSessionSubsystem.h"


void UBNGameResultActivatableWidget::SetResultTextBlock(FText Text)
{
	ResultTextBlock->SetText(Text);
}

void UBNGameResultActivatableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(!LeaveGameButton->OnPressed.Contains(this, "LeaveGame"))
	{
		LeaveGameButton->OnPressed.AddDynamic(this, &UBNGameResultActivatableWidget::LeaveGame);
	}
}

void UBNGameResultActivatableWidget::LeaveGame()
{
	UBNSessionSubsystem* SessionSubsystem = GetGameInstance()->GetSubsystem<UBNSessionSubsystem>();
	if (GetWorld()->GetNetMode() == NM_ListenServer)
	{
		SessionSubsystem->DestroySession();
	}

	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu", true);
}
