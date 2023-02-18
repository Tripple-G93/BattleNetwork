// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActivatableWidgets/BNStackActivatableWidget.h"
#include "BNFindSessionActivatableWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNFindSessionActivatableWidget : public UBNStackActivatableWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonBack;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ButtonJoinFirstResult;
	
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void JoinFirstSession();

	void SetInputModeToGameplay() const;
};
