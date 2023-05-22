// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableWidgets/BNStackActivatableWidget.h"
#include "BNMainMenuActivatableWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNMainMenuActivatableWidget : public UBNStackActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateSinglePlayerGame;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UButton> ButtonWhatIsNew;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UButton> ButtonCredits;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI")
	TSubclassOf<UCommonActivatableWidget> FindSessionActivatableWidgetClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI")
	TSubclassOf<UCommonActivatableWidget> WhatIsNewActivatableWidgetClass;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|UI")
	TSubclassOf<UCommonActivatableWidget> CreditsActivatableWidgetClass;

	UPROPERTY(EditAnywhere, Category = "BN|MapName")
	FName MultiplayerMapName;

protected:
	virtual void NativeConstruct() override;

private:

    void AddWidgetToStack(TSubclassOf<UCommonActivatableWidget> ActivatableWidgetClass);

	void SetInputModeToGameplay() const;

    void BindButtonWidgets();

    UFUNCTION()
    void CreateSinglePlayerGame();

    UFUNCTION()
    void WhatIsNewWidgetFlow();

    UFUNCTION()
    void CreditsWidgetFlow();
};
