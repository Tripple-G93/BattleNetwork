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
	TObjectPtr<UButton> ButtonCreateLocalMultiplayerGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreateSinglePlayerGame;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonFindGame;

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
