// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BNCommonActivatableWidget.generated.h"

class ActivatableWidgetT;
class UButton;
class UCommonActivatableWidgetStack;
/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNCommonActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

	UCommonActivatableWidget* FindSessionActivatableWidget;
	
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateLocalMultiplayerGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateSinglePlayerGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonFindGame;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> CommonActivatableWidgetStack;

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
