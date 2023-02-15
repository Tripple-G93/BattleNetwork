// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "BNGameResultActivatableWidget.generated.h"

class UButton;
class UCommonTextBlock;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNGameResultActivatableWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> ResultTextBlock;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> LeaveGameButton;

public:

	void SetResultTextBlock(FText Text);

protected:
	virtual void NativeConstruct() override;

private:

	UFUNCTION()
	void LeaveGame();
};
