// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/BNGameModeBase.h"

#include "Actors/BNGridActor.h"
#include "Actors/BNProjectilePool.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNPlayerController.h"
#include "Engine/World.h"

ABNGameModeBase::ABNGameModeBase()
{
	MaxPlayersOnGrid = 2;
}


void ABNGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	SpawnGrid();

	SpawnObjectPool();
	
	GridActor->CreateGrid();
}

void ABNGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	PlayerControllers.Add(NewPlayer);

	if(PlayerControllers.Num() == 1)
	{
		GridActor->SpawnPlayer1(NewPlayer);
		GridActor->GetPlayer1Pawn()->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");
	}
	else if(PlayerControllers.Num() == 2)
	{
		GridActor->SpawnPlayer2(NewPlayer);
		GridActor->GetPlayer2Pawn()->GetBaseAttributeSet()->OnPlayerDeathDelegate.AddUFunction(this, "GameHasEnded");
	}
}

void ABNGameModeBase::GameHasEnded(AController* Controller)
{
	// Do a check if player controller is null then return and honestly do an ensure because that should not be the case
	if(!ensure(Controller))
	{
		return;
	}

	for(int index = 0; index < PlayerControllers.Num(); ++index)
	{
		if(Controller != PlayerControllers[index])
		{
			Cast<ABNPlayerController>(PlayerControllers[index])->DisplayWinResultUI();
		}
		else
		{
			Cast<ABNPlayerController>(PlayerControllers[index])->DisplayLossResultUI();
		}
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

TObjectPtr<ABNProjectilePool> ABNGameModeBase::GetBulletProjectilePool()
{
	return BulletProjectilePool;
}

ABNGridActor* ABNGameModeBase::GetGridActor()
{
	return GridActor;
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

void ABNGameModeBase::SpawnObjectPool()
{
	if(ensure(BulletProjectilePoolSubClass))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		SpawnParameters.OverrideLevel = GetLevel();

		BulletProjectilePool = GetWorld()->SpawnActor<ABNProjectilePool>(BulletProjectilePoolSubClass, SpawnParameters);
	}
}
