// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Slider.h"
#include "BNCreateSession.generated.h"

class UButton;
class UCheckBox;
class USlider;

UCLASS()
class BATTLENETWORK_API UBNCreateSession : public UUserWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> SliderNumberPlayers;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckBox> CheckBoxEnableLocalNetwork;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonCreate;

public:
	virtual bool Initialize() override;

protected:

	UFUNCTION()
	void CreateSession();
};
