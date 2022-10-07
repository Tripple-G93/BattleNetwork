// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BNEntityPawn.generated.h"

class UDataTable;
class UPaperFlipbookComponent;

UCLASS()
class BATTLENETWORK_API ABNEntityPawn : public APawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> FlipbookAnimationDataTable;
public:
	// Sets default values for this pawn's properties
	ABNEntityPawn(const FObjectInitializer& ObjectInitializer);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



};
