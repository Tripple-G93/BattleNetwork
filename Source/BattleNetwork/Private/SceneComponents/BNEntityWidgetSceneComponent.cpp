// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneComponents/BNEntityWidgetSceneComponent.h"

#include "Blueprint/UserWidget.h"
#include "UserWidgets/BNEntityUserWidget.h"

// Sets default values for this component's properties
UBNEntityWidgetSceneComponent::UBNEntityWidgetSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;


}


// Called when the game starts
void UBNEntityWidgetSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeEntityUserWidget();
	
}

void UBNEntityWidgetSceneComponent::InitializeEntityUserWidget()
{
	if(ensure(EntityUserWidgetClass))
	{
		ensure(EntityUserWidget == nullptr);

		EntityUserWidget = CreateWidget<UBNEntityUserWidget>(GetWorld(), EntityUserWidgetClass);
		EntityUserWidget->AttachedActor = GetOwner();
		EntityUserWidget->AddToViewport();

		// TODO BN: We want to initialize the widget function here or by the widget class itself
		// since we now have the attached actor
		// We want to also set up the bindings for this widget as well. 
	}
}
