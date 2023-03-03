// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controllers/BNBasePlayerController.h"
#include "BNPlayerController.generated.h"

class UCommonActivatableWidget;
class UBNGameResultActivatableWidget;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNPlayerController : public ABNBasePlayerController
{
	GENERATED_BODY()


protected:

	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI|Result")
	TSubclassOf<UCommonActivatableWidget> ResultActivatableWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "BN|UI|Result")
	TObjectPtr<UBNGameResultActivatableWidget> ResultActivatableWidget;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText WinResultText;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FText LossResultText;
	
public:

	UFUNCTION(Client, Reliable)
	void DisplayWinResultUI();

	UFUNCTION(Client, Reliable)
	void DisplayLossResultUI();

private:
	
	void SetInputModeUI();

	void CreateResultWidget(FText text);
};
