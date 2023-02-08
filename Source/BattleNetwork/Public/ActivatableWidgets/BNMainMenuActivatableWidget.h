// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BNMainMenuActivatableWidget.generated.h"

class ActivatableWidgetT;
class UButton;
class UCommonActivatableWidgetStack;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNMainMenuActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

	UCommonActivatableWidget* FindSessionActivatableWidget;
	
protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateLocalMultiplayerGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateSinglePlayerGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonFindGame;

	//UPROPERTY(meta = (BindWidget))
	//TObjectPtr<UCommonActivatableWidgetStack> FindLocalMultiplayerGameWidgetStack;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI")
	TSubclassOf<UCommonActivatableWidget> FindSessionActivatableWidgetClass;

	UPROPERTY(EditAnywhere, Category = "BN|MapName")
	FName MultiplayerMapName;

public:

	virtual bool Initialize() override;

private:

	UFUNCTION()
	void AddFindSessionActivatableWidgetToStack();

	UFUNCTION()
	void CreateLocalMultiplayerGame();
};
