// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Overlay.h"
#include "BNWorldSpaceToWidgetUserWidget.generated.h"

class UOverlay;
class USceneComponent;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNWorldSpaceToWidgetUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> Overlay;

	UPROPERTY(EditAnywhere, Category = "BN|UI")
	FVector WorldOffset;

	UPROPERTY(BlueprintReadWrite, Category = "BN|UI", meta = (ExposeOnSpawn=true))
	TObjectPtr<AActor> AttachedActor;
	
	UPROPERTY(BlueprintReadWrite, Category = "BN|UI", meta = (ExposeOnSpawn=true))
	TObjectPtr<USceneComponent> AttachedSceneComponent;
	
public:

	void SetAttachedActor(AActor* OwningActor);
	
	void SetAttachedComponent(USceneComponent* SceneComponent);
	
protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetScreenPositionFromWorldSpace();
};
