// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BNCreateSession.h"
#include "Blueprint/UserWidget.h"
#include "BNMainMenuUserWidget.generated.h"

class UBorder;
class UButton;
class UBNCreateSession;
class UBNFindSessionUserWidget;

UCLASS()
class BATTLENETWORK_API UBNMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> BorderMainMenu;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateLocalMultiplayerGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateSinglePlayerGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonFindGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBNFindSessionUserWidget> FindSessionWidget;

	UPROPERTY(EditAnywhere, Category = "BN|MapName")
	FName MultiplayerMapName;

public:

	virtual bool Initialize() override;
	
protected:

	UFUNCTION()
	void CreateLocalMultiplayerGame();
	
	UFUNCTION()
	void ShowFindSessionMenu();

	UFUNCTION()
	void HideFindSessionMenu();

};
