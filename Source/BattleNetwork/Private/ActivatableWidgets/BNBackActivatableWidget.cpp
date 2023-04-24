// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableWidgets/BNBackActivatableWidget.h"

#include "Components/Button.h"

void UBNBackActivatableWidget::NativeConstruct()
{
    if (!ButtonBack->OnPressed.Contains(this, "DeactivateWidget"))
    {
        ButtonBack->OnPressed.AddDynamic(this, &UBNBackActivatableWidget::DeactivateWidget);
    }
}
