// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BNFindSessionUserWidget.generated.h"

class UButton;
class UCheckBox;

UCLASS()
class BATTLENETWORK_API UBNFindSessionUserWidget : public UUserWidget
{
private:
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonBack;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonJoinFirstResult;

public:

	virtual bool Initialize() override;
	
	UButton* GetBackButton();

protected:

	UFUNCTION()
	void JoinFirstSession();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
