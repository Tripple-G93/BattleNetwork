// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "BNUtilityStatics.generated.h"

class UDataTable;
class UPaperFlipbookComponent;

struct FBNFlipbookAnimationTableInfoRow;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNUtilityStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	static FBNFlipbookAnimationTableInfoRow* UpdateAnimation(UDataTable* FlipbookAnimationDataTable, FBNFlipbookAnimationTableInfoRow* CurrentFlipbookAnimationTableInfoRow,
		UPaperFlipbookComponent* PaperFlipbookComponent, FGameplayTag NewStatus );
	
};
