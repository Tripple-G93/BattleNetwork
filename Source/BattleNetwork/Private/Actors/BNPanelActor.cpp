// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNPanelActor.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ABNPanelActor::ABNPanelActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
}

void ABNPanelActor::SetPanelStatus(FGameplayTag NewStatus)
{
	ensure(FlipbookAnimationDataTable);

	if (!CurrentFlipbookAnimationTableInfoRow || CurrentFlipbookAnimationTableInfoRow->AnimationGameplayTag != NewStatus)
	{
		TArray<FBNFlipbookAnimationTableInfoRow*> FlipbookAnimationTableRows;
		FlipbookAnimationDataTable->GetAllRows("", FlipbookAnimationTableRows);

		for (FBNFlipbookAnimationTableInfoRow* Entry : FlipbookAnimationTableRows)
		{
			if (NewStatus == Entry->AnimationGameplayTag)
			{
				CurrentFlipbookAnimationTableInfoRow = Entry;
				PaperFlipbookComponent->SetFlipbook(Entry->PaperFlipbook);

				break;
			}
		}
	}
}

