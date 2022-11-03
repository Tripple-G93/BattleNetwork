// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNWorldSpaceToWidgetUserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

void UBNWorldSpaceToWidgetUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(ensure(AttachedSceneComponent) && ensure(AttachedActor))
	{
		SetScreenPositionFromWorldSpace();
	}
}

void UBNWorldSpaceToWidgetUserWidget::SetAttachedActor(AActor* OwningActor)
{
	AttachedActor = OwningActor;
}

void UBNWorldSpaceToWidgetUserWidget::SetAttachedComponent(USceneComponent* SceneComponent)
{
	AttachedSceneComponent = SceneComponent;
}

void UBNWorldSpaceToWidgetUserWidget::SetScreenPositionFromWorldSpace()
{
	FVector2D ScreenPosition;
	FVector Widget3DLocation =  AttachedActor->GetActorLocation() + AttachedSceneComponent->GetRelativeLocation();
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), Widget3DLocation + WorldOffset, ScreenPosition);

	if (bIsOnScreen)
	{
		const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition /= Scale;

		FVector2d OverlaySize = Overlay->GetDesiredSize();
		ScreenPosition.X -= OverlaySize.X / 2;
		
		SetRenderTranslation(ScreenPosition);
	}

	UpdateVisibility(bIsOnScreen);
}

void UBNWorldSpaceToWidgetUserWidget::UpdateVisibility(const bool bIsOnScreen)
{
	//if (ParentSizeBox)
	{
		//ParentSizeBox->SetVisibility(bIsOnScreen ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
	}
}

