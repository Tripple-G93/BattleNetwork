// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BNMainMenuStackActivatableWidget.generated.h"

class UBNStackActivatableWidget;
class UCommonActivatableWidgetStack;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNMainMenuStackActivatableWidget : public UCommonActivatableWidget
{
private:
	GENERATED_BODY()

	UBNStackActivatableWidget* MainMenuActivatableWidget;
	
protected:
	
	UPROPERTY(meta = (BindWidget))
    TObjectPtr<UCommonActivatableWidgetStack> MainMenuWidgetStack;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BN|MainMenuUI")
    TSubclassOf<UCommonActivatableWidget> MainMenuActivatableWidgetClass;
    
public:

    virtual bool Initialize() override;

protected:
	virtual void NativeConstruct() override;
};
