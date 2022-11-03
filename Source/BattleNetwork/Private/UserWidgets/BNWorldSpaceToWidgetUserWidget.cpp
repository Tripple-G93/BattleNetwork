// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidgets/BNWorldSpaceToWidgetUserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

void UBNWorldSpaceToWidgetUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	RemoveFromParentIfNotValid();

	SetScreenPositionFromWorldSpace();
}

void UBNWorldSpaceToWidgetUserWidget::RemoveFromParentIfNotValid()
{
	if (!IsValid(AttachedActor))
	{
		RemoveFromParent();

		UE_LOG(LogTemp, Warning, TEXT("AttachedActor no longer valid, removing Health Widget."));
		return;
	}
}

void UBNWorldSpaceToWidgetUserWidget::SetScreenPositionFromWorldSpace()
{
	FVector2D ScreenPosition;
	bool bIsOnScreen = UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition);

	if (bIsOnScreen)
	{
		const float Scale = UWidgetLayoutLibrary::GetViewportScale(this);

		ScreenPosition /= Scale;

		//ParentSizeBox->
		//if (ParentSizeBox)
		{
			//ParentSizeBox->SetRenderTranslation(ScreenPosition);
			SetRenderTranslation(ScreenPosition);
		}
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

