// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BNMainMenuStackActivatableWidget.generated.h"

class UCommonActivatableWidgetStack;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNMainMenuStackActivatableWidget : public UCommonActivatableWidget
{
private:
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> MainMenuWidgetStack;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|MainMenuUI")
    TSubclassOf<UCommonActivatableWidget> MainMenuActivatableWidgetClass;
	
	virtual void NativeConstruct() override;
};
