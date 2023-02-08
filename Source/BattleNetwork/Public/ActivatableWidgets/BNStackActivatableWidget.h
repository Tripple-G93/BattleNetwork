// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BNStackActivatableWidget.generated.h"

class UCommonActivatableWidgetStack;
/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNStackActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	TObjectPtr<UCommonActivatableWidgetStack> CommonActivatableWidgetStackReference;

public:

	void SetCommonActivatableWidgetStackReference(UCommonActivatableWidgetStack* CommonActivatableWidgetStack);

	UCommonActivatableWidgetStack* GetCommonActivatableWidgetStackReference();
};
