// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BNGameModeBase.generated.h"

class ABNGridActor;

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API ABNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABNGridActor> GridSubClassActor;

	TObjectPtr<ABNGridActor> GridActor;

	TArray<APlayerController*> PlayerControllers;
public:
	TArray<APlayerController*>& GetPlayerControllers();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
