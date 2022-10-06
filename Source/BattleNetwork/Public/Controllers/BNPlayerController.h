// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BNPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:

	// Server only
	virtual void OnPossess(APawn* InPawn) override;
};
