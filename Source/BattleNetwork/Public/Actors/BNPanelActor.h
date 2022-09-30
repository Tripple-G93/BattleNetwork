// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tables/BNFlipbookAnimationTable.h"
#include "BNPanelActor.generated.h"

class UDataTable;
class UPaperFlipbookComponent;

UCLASS()
class BATTLENETWORK_API ABNPanelActor : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> FlipbookAnimationDataTable;

	TObjectPtr<FBNFlipbookAnimationTableInfoRow> CurrentFlipbookAnimationTableInfoRow;
	
public:	
	// Sets default values for this actor's properties
	ABNPanelActor(const FObjectInitializer& ObjectInitializer);

protected:

public:	

	void SetPanelStatus(FGameplayTag NewStatus);

};