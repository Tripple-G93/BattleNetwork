// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BNCreateSession.h"
#include "Blueprint/UserWidget.h"
#include "BNMainMenuUserWidget.generated.h"

class UBorder;
class UButton;
class UBNCreateSession;

UCLASS()
class BATTLENETWORK_API UBNMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> BorderMainMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBNCreateSession> CreateSessionWidget;

public:

	virtual bool Initialize() override;
	
protected:

	UFUNCTION()
	void ShowCreateGameMenu();

};
