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
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonBack;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonFindSession;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonJoinFirstResult;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CheckBoxEnableNetworkSession;

public:

	virtual bool Initialize() override;
	
	UButton* GetBackButton();

protected:

	UFUNCTION()
	void FindSession();

	UFUNCTION()
	void JoinFirstSession();
	
};
