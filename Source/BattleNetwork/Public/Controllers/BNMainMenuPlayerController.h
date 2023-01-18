// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BNMainMenuPlayerController.generated.h"

class UUserWidget;

UCLASS()
class BATTLENETWORK_API ABNMainMenuPlayerController : public APlayerController
{
private:
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI")
	TSubclassOf<UUserWidget> MainMenuUserWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "BN|UI")
	TObjectPtr<UUserWidget> MainMenuUserWidget;

public:
	
protected:
	virtual void OnRep_PlayerState() override;

private:

	void CreateMainMenu();
protected:
	
	virtual void BeginPlay() override;
};
