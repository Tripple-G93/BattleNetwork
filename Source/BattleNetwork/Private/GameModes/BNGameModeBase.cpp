// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeBase.h"
#include "Actors/BNGridActor.h"
#include "Engine/World.h"

void ABNGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// We want to spawn the grid if it does exist
	if(ensure(GridSubClassActor))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.OverrideLevel = GetLevel();

		GridActor = GetWorld()->SpawnActor<ABNGridActor>(GridSubClassActor, FVector(0,0,0), FRotator(0,0,0), SpawnParameters);
	}
}

void ABNGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllers.Add(NewPlayer);
}

TArray<APlayerController*>& ABNGameModeBase::GetPlayerControllers()
{
	return PlayerControllers;
}