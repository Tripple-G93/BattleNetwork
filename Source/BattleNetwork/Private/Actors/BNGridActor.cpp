// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNGridActor.h"
#include "Actors/BNPanelActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

// Sets default values
ABNGridActor::ABNGridActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true; 
	
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SceneComponent);
	
	GridWidth = 6;
	GridHeight = 3;

	PanelSpacingWidth = 24;
	PanelSpacingHeight = 40;
	
	IsPlayer1Spawned = false;
	IsPlayer2Spawned = false;

	PlayerSpawnOffset = 0;
}

void ABNGridActor::SpawnPlayers_Implementation(APlayerController* PlayerController)
{
	if(ensure(PlayerPawnSubclass) && (!IsPlayer1Spawned || !IsPlayer2Spawned))
	{
		int32 CenterX = GridWidth  / 4;
		int32 CenterY = GridHeight / 2;
		FRotator Rotation;
		
		if(!IsPlayer1Spawned)
		{
			// Add the gameplay tag here for the player?
			IsPlayer1Spawned = true;
		}
		else
		{
			CenterX = GridWidth - CenterX - 1;
			CenterY = GridHeight - CenterY - 1;
			Rotation.Yaw = 180;
			IsPlayer2Spawned = true;
		}

		ABNPanelActor* Panel = Grid[CenterX][CenterY];
		const FVector Location = Panel->GetActorLocation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;

		ABNPlayerPawn* Player = GetWorld()->SpawnActor<ABNPlayerPawn>(PlayerPawnSubclass, Location, Rotation, SpawnParameters);
		PlayerController->Possess(Player);
		PlayerController->SetViewTarget(this);
		Panel->SetEntityPawn(Player);
	}
}

// Called when the game starts or when spawned
void ABNGridActor::BeginPlay()
{
	Super::BeginPlay();
}

void ABNGridActor::CreateGrid()
{
	if (ensure(PanelActorSubclass))
	{
		for (int32 XIndex = 0; XIndex < GridWidth; ++XIndex)
		{
			Grid.Add(FBNPannel2DArray());
			for (int32 YIndex = 0; YIndex < GridHeight; ++YIndex)
			{
				SpawnPanel(XIndex, YIndex);
			}
		}
	}
}

void ABNGridActor::SpawnPanel(const int32 XIndex, const int32 YIndex)
{
	const FVector Location(XIndex * PanelSpacingWidth, YIndex * PanelSpacingHeight, 0);
	const FRotator Rotation;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	UWorld* World = GetWorld();

	ABNPanelActor* NewPanelActor = World->SpawnActor<ABNPanelActor>(PanelActorSubclass, Location, Rotation, SpawnParameters);
	if (XIndex < GridWidth / 2)
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


