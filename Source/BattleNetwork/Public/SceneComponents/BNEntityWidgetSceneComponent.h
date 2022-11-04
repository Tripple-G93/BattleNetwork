// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BNEntityWidgetSceneComponent.generated.h"

class UBNEntityUserWidget;
class UUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLENETWORK_API UBNEntityWidgetSceneComponent : public USceneComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TObjectPtr<UBNEntityUserWidget> EntityUserWidget;

	UPROPERTY(EditDefaultsOnly, Category = "BN|UI")
	TSubclassOf<UUserWidget> EntityUserWidgetClass;

public:	

	UBNEntityWidgetSceneComponent();
	
	void InitializeEntityUserWidget();
	
};
