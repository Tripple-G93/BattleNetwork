// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneComponents/BNEntityWidgetSceneComponent.h"

#include "UserWidgets/BNEntityUserWidget.h"

#include <Blueprint/UserWidget.h>

// Sets default values for this component's properties
UBNEntityWidgetSceneComponent::UBNEntityWidgetSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

    IsInitialized = false;
}

void UBNEntityWidgetSceneComponent::CreateEntityUserWidget()
{
    if (EntityUserWidget == nullptr && ensure(EntityUserWidgetClass))
    {
        EntityUserWidget = CreateWidget<UBNEntityUserWidget>(GetWorld(), EntityUserWidgetClass);
        EntityUserWidget->SetAttachedActor(GetOwner());
        EntityUserWidget->SetAttachedComponent(this);
    }
}

void UBNEntityWidgetSceneComponent::InitializeEntityUserWidget()
{
	if(IsInitialized == false)
	{
		EntityUserWidget->InitializeWidgetWithAttributes();
		EntityUserWidget->InitializeAttributeBindingsToWidget();
        IsInitialized = true;
	}
}

void UBNEntityWidgetSceneComponent::ActivateEntityUserWidget()
{
    if (!EntityUserWidget->IsInViewport())
    {
        EntityUserWidget->AddToViewport();
    }
}

void UBNEntityWidgetSceneComponent::DeactivateEntityUserWidget()
{
    if (EntityUserWidget->IsInViewport())
    {
        EntityUserWidget->RemoveFromParent();
    }
}
