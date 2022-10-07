// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNGridActor.h"
#include "Actors/BNPanelActor.h"
#include "Engine/World.h"

// Sets default values
ABNGridActor::ABNGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GridWidth = 6;
	GridHeight = 3;

	PanelSpacingWidth = 24;
	PanelSpacingHeight = 40;
	
	IsPlayer1Spawned = false;
	IsPlayer2Spawned = false;

	PlayerSpawnOffset = 0;
}

// Called when the game starts or when spawned
void ABNGridActor::BeginPlay()
{
	Super::BeginPlay();

	CreateGrid();
}

void ABNGridActor::CreateGrid()
{
	if (ensure(PanelActor))
	{
		for (int32 XIndex = 0; XIndex < GridHeight; ++XIndex)
		{
			Grid.Add(FBNPannel2DArray());
			for (int32 YIndex = 0; YIndex < GridWidth; ++YIndex)
			{
				SpawnPanel(XIndex, YIndex);
			}
		}
	}
}

void ABNGridActor::SpawnPanel(const int32 XIndex, const int32 YIndex)
{
	const FVector Location(XIndex * PanelSpacingWidth, YIndex * PanelSpacingHeight, 10);
	const FRotator Rotation;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	UWorld* World = GetWorld();

	ABNPanelActor* NewPanelActor = World->SpawnActor<ABNPanelActor>(PanelActor, Location, Rotation, SpawnParameters);
	if (YIndex < GridWidth / 2)
	{
		static FGameplayTag PanelRedOriginalTag = FGameplayTag::RequestGameplayTag("Panel.Red.Original");
		NewPanelActor->SetPanelStatus(PanelRedOriginalTag);
	}
	else
	{
		static FGameplayTag PanelBlueOriginalTag = FGameplayTag::RequestGameplayTag("Panel.Blue.Original");
		NewPanelActor->SetPanelStatus(PanelBlueOriginalTag);
	}

	Grid[XIndex].Add(NewPanelActor);
}

void ABNGridActor::SpawnPlayers(APlayerController* PlayerController)
{
	if(ensure(PlayerPawnSubclass) && (!IsPlayer1Spawned || !IsPlayer2Spawned))
	{
		
	}
}



