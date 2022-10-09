// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BNEntityPawn.h"
#include "BNPlayerPawn.generated.h"

UCLASS()
class BATTLENETWORK_API ABNPlayerPawn : public ABNEntityPawn
{
	GENERATED_BODY()

public:
	ABNPlayerPawn(const FObjectInitializer& ObjectInitializer);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
