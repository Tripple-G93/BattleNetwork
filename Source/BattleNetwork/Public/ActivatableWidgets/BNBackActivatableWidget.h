// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableWidgets/BNStackActivatableWidget.h"
#include "BNBackActivatableWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNBackActivatableWidget : public UBNStackActivatableWidget
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonBack;

    void NativeConstruct() override;

};
