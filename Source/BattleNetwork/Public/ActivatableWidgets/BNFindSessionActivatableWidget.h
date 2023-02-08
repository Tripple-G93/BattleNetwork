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

public:

	virtual bool Initialize() override;
	
	UButton* GetBackButton();

protected:

	UFUNCTION()
	void JoinFirstSession();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
