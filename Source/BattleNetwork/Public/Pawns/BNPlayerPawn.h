// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BNEntityPawn.h"
#include "BNPlayerPawn.generated.h"

UCLASS()
class BATTLENETWORK_API ABNPlayerPawn : public ABNEntityPawn
{
	GENERATED_BODY()

protected:

	bool ASCInputBound;
	
public:
	ABNPlayerPawn(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void AttemptToMovePlayerEntityHorizontally(const float Value);
    void AttemptToMovePlayerEntityVertically(const float Value);

protected:

	// Called from both SetupPlayerInputComponent and OnRep_PlayerState because of a potential race condition where the PlayerController might
	// call ClientRestart which calls SetupPlayerInputComponent before the PlayerState is repped to the client so the PlayerState would be null in SetupPlayerInputComponent.
	// Conversely, the PlayerState might be repped before the PlayerController calls ClientRestart so the Actor's InputComponent would be null in OnRep_PlayerState.
	void BindASCInput();
	
	virtual void OnRep_PlayerState() override;

};
