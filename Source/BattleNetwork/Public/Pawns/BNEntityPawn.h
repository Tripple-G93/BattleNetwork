// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BNBasePawn.h"
#include "BNEntityPawn.generated.h"

class UDataTable;
class UPaperFlipbookComponent;
class USceneComponent;

UCLASS()
class BATTLENETWORK_API ABNEntityPawn : public ABNBasePawn
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> FlipbookAnimationDataTable;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;

public:
	
	ABNEntityPawn(const FObjectInitializer& ObjectInitializer);

	void FlipEntity() const;
	
protected:

	virtual void BeginPlay() override;

};
