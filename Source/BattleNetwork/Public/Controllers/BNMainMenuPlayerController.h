// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controllers/BNBasePlayerController.h"
#include "BNMainMenuPlayerController.generated.h"

class UCommonActivatableWidget;

UCLASS()
class BATTLENETWORK_API ABNMainMenuPlayerController : public ABNBasePlayerController
{
private:
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI")
	TSubclassOf<UCommonActivatableWidget> MainMenuUserWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "BN|UI")
	TObjectPtr<UCommonActivatableWidget> MainMenuUserWidget;
	
	virtual void BeginPlay() override;
	
private:

	void CreateMainMenu();
	
    void SetInputModeUI();
};
