// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include <GameplayTagContainer.h>
#include "BNFlipbookAnimationTable.generated.h"

class UPaperFlipbook;
class USoundCue;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBNFlipbookAnimationTableInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPaperFlipbook> PaperFlipbook;

	UPROPERTY(EditDefaultsOnly)
	bool bDoesLoop;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag AnimationGameplayTag;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundCue> SoundEffectSoundCue;
};
