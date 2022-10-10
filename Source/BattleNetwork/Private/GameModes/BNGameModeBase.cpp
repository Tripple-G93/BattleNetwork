// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeBase.h"
#include "Actors/BNGridActor.h"
#include "Engine/World.h"

ABNGameModeBase::ABNGameModeBase()
{
	MaxPlayersOnGrid = 2;
}


void ABNGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	SpawnGrid();
	
	GridActor->CreateGrid();
}

void ABNGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllers.Add(NewPlayer);

	if(PlayerControllers.Num() == 1)
	{
		GridActor->SpawnPlayer1(NewPlayer);
	}
	else if(PlayerControllers.Num() == 2)
	{
		GridActor->SpawnPlayer2(NewPlayer);
	}
}

int ABNGameModeBase::GetMaxPlayersOnGrid() const
{
	return MaxPlayersOnGrid;
}

TArray<APlayerController*>& ABNGameModeBase::GetPlayerControllers()
{
	return PlayerControllers;
}

void ABNGameModeBase::SpawnGrid()
{
	if(ensure(GridActorSubClass))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.OverrideLevel = GetLevel();

		GridActor = GetWorld()->SpawnActor<ABNGridActor>(GridActorSubClass, FVector(0,0,0), FRotator(0,0,0), SpawnParameters);
	}
}