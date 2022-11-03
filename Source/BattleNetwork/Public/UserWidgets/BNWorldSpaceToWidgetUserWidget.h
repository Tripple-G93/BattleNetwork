// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BNWorldSpaceToWidgetUserWidget.generated.h"

class UCanvas;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNWorldSpaceToWidgetUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WorldOffset;

	UPROPERTY(BlueprintReadWrite, Category = "UI", meta = (ExposeOnSpawn=true))
	TObjectPtr<AActor> AttachedActor;

protected:

	void RemoveFromParentIfNotValid();

	void SetScreenPositionFromWorldSpace();

	void UpdateVisibility(const bool bIsOnScreen);
};
