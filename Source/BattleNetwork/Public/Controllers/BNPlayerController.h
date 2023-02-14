// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BNPlayerController.generated.h"

class UCommonActivatableWidget;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:

	// Server only
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI")
	TSubclassOf<UCommonActivatableWidget> ResultActivatableWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "BN|UI")
	TObjectPtr<UCommonActivatableWidget> ResultActivatableWidget;
	
public:

	UFUNCTION(Client, Reliable)
	void DisplayWinResultUI();

	UFUNCTION(Client, Reliable)
	void DisplayLossResultUI();

private:
	
	void SetInputModeUI();
};
