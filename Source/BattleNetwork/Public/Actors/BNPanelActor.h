// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tables/BNFlipbookAnimationTable.h"
#include "BNPanelActor.generated.h"

class ABNEntityPawn;
class UDataTable;
class UPaperFlipbookComponent;
class USceneComponent;

UCLASS()
class BATTLENETWORK_API ABNPanelActor : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(EditDefaultsOnly, Category = "BN")
	TObjectPtr<UDataTable> FlipbookAnimationDataTable;

	UPROPERTY(Replicated)
	TObjectPtr<ABNEntityPawn> EntityPawn;
	
	FBNFlipbookAnimationTableInfoRow* CurrentFlipbookAnimationTableInfoRow;
	
public:	
	// Sets default values for this actor's properties
	ABNPanelActor(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/*
	 * SETTERS
	 */

	void SetEntityPawn(ABNEntityPawn* NewEntityPawn);
	
	/*
	 * GETTERS
	 */

	TObjectPtr<ABNEntityPawn> GetEntityPawn();
	
protected:

public:	

	void SetPanelStatus(FGameplayTag NewStatus);

};
