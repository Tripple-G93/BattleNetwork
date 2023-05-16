// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include <GameplayTagContainer.h>
#include "BNPaperFlipbookComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNFlipbookFoundSocket, FTransform, FlipbookSocketTransform);

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNPaperFlipbookComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
	
public:

    FBNFlipbookFoundSocket OnFoundSocket;

protected:

    bool ShouldCheckForSocket;

    FName PaperSpriteSocketName;

public:

    UBNPaperFlipbookComponent(const FObjectInitializer& ObjectInitializer);

    void SocketToLookFor(FName NewPaperSpriteSocketName);

    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

    void FindSocket();

};
