// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/BNUtilityStatics.h"

#include "Tables/BNFlipbookAnimationTable.h"

#include <PaperFlipbookComponent.h>

FBNFlipbookAnimationTableInfoRow* UBNUtilityStatics::UpdateAnimation(UDataTable* FlipbookAnimationDataTable,
	FBNFlipbookAnimationTableInfoRow* CurrentFlipbookAnimationTableInfoRow, UPaperFlipbookComponent* PaperFlipbookComponent, FGameplayTag NewStatus )
{
	if (ensure(FlipbookAnimationDataTable) && (!CurrentFlipbookAnimationTableInfoRow || CurrentFlipbookAnimationTableInfoRow->AnimationGameplayTag != NewStatus))
	{
		TArray<FBNFlipbookAnimationTableInfoRow*> FlipbookAnimationTableRows;
		FlipbookAnimationDataTable->GetAllRows("", FlipbookAnimationTableRows);

		for (FBNFlipbookAnimationTableInfoRow* Entry : FlipbookAnimationTableRows)
		{
			if (NewStatus == Entry->AnimationGameplayTag)
			{
				PaperFlipbookComponent->SetFlipbook(Entry->PaperFlipbook);
				PaperFlipbookComponent->SetLooping(Entry->bDoesLoop);
				return Entry;
			}
		}

		UE_LOG(LogTemp, Error, TEXT("Unable to find flipbook animation of : %s."), *NewStatus.GetTagName().ToString());
	}

	return CurrentFlipbookAnimationTableInfoRow;
}
