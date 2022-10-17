// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNGridActor.h"
#include "AbilitySystemComponent.h"
#include "Actors/BNPanelActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "Net/UnrealNetwork.h"

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

	GridDividerIndex = 2;

	PanelSpacingWidth = 24;
	PanelSpacingHeight = 40;

	PlayerSpawnOffset = 0;
}

void ABNGridActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABNGridActor, Grid);
}

void ABNGridActor::SpawnPlayer1_Implementation(APlayerController* PlayerController)
{
	// TODO BN: When you actually handle player spawning be sure to unify the similarity between the spawn player functions
	if(ensure(PlayerPawnSubclass))
	{
		const int32 CenterX = 0;
		const int32 CenterY = GridHeight / 2;
		const FRotator Rotation;

		ABNPanelActor* Panel = Grid[CenterX][CenterY];
		const FVector Location = Panel->GetActorLocation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = PlayerController;

		ABNPlayerPawn* Player = GetWorld()->SpawnActor<ABNPlayerPawn>(PlayerPawnSubclass, Location, Rotation, SpawnParameters);
		PlayerController->Possess(Player);
		PlayerController->SetViewTarget(this);
		Panel->SetEntityPawn(Player);
		Player->SetTeamTag(FGameplayTag::RequestGameplayTag("Team1"));
		Player->SetGridActorReference(this);
		Player->SetNewXIndexPosition(CenterX);
		Player->SetNewYIndexPosition(CenterY);
	}
}

void ABNGridActor::SpawnPlayer2_Implementation(APlayerController* PlayerController)
{
	// TODO BN: When you actually handle player spawning be sure to unify the similarity between the spawn player functions
	if(ensure(PlayerPawnSubclass))
	{
		const int32 CenterX = GridWidth - 1;
		int32 CenterY = GridHeight / 2;
		CenterY = GridHeight - CenterY - 1;
		
		FRotator Rotation;
		Rotation.Yaw = 180;

		ABNPanelActor* Panel = Grid[CenterX][CenterY];
		const FVector Location = Panel->GetActorLocation();
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = PlayerController;

		ABNPlayerPawn* Player = GetWorld()->SpawnActor<ABNPlayerPawn>(PlayerPawnSubclass, Location, Rotation, SpawnParameters);
		PlayerController->Possess(Player);
		PlayerController->SetViewTarget(this);
		Panel->SetEntityPawn(Player);
		Player->FlipEntity();
		Player->SetTeamTag(FGameplayTag::RequestGameplayTag("Team2"));
		Player->SetGridActorReference(this);
		Player->SetNewXIndexPosition(CenterX);
		Player->SetNewYIndexPosition(CenterY);
	}
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

bool ABNGridActor::CanEntityMoveLeft(const ABNEntityPawn* EntityPawn)
{
	const int32 XIndex = EntityPawn->GetXIndexPosition();
	const int32 YIndex = EntityPawn->GetYIndexPosition();
	
	if(EntityPawn->GetTeamTag() == FGameplayTag::RequestGameplayTag(FName("Team1")))
	{
		return XIndex > 0 && Grid[XIndex - 1][YIndex]->GetEntityPawn() == nullptr;
	}
	else
	{
		return XIndex > GridDividerIndex + 1 && Grid[XIndex - 1][YIndex]->GetEntityPawn() == nullptr;
	}
}

bool ABNGridActor::CanEntityMoveRight(const ABNEntityPawn* EntityPawn)
{
	const int32 XIndex = EntityPawn->GetXIndexPosition();
	const int32 YIndex = EntityPawn->GetYIndexPosition();

	if(EntityPawn->GetTeamTag() == FGameplayTag::RequestGameplayTag(FName("Team1")))
	{
		return XIndex < GridDividerIndex && Grid[XIndex + 1][YIndex]->GetEntityPawn() == nullptr;
	}
	else
	{
		return XIndex < GridWidth - 2 && Grid[XIndex + 1][YIndex]->GetEntityPawn() == nullptr;
	}
}

bool ABNGridActor::CanEntityMoveUp(const ABNEntityPawn* EntityPawn)
{
	const int32 XIndex = EntityPawn->GetXIndexPosition();
	const int32 YIndex = EntityPawn->GetYIndexPosition();
	
	return YIndex > 0 && Grid[XIndex][YIndex - 1]->GetEntityPawn() == nullptr;
}

bool ABNGridActor::CanEntityMoveDown(const ABNEntityPawn* EntityPawn)
{
	const int32 XIndex = EntityPawn->GetXIndexPosition();
	const int32 YIndex = EntityPawn->GetYIndexPosition();

	return YIndex < GridHeight - 1 && Grid[XIndex][YIndex + 1]->GetEntityPawn() == nullptr;
}

void ABNGridActor::MoveEntityToNewPanel(ABNEntityPawn* EntityPawn, int32 NewXIndex, int32 NewYIndex)
{
	const int32 OldXIndex = EntityPawn->GetXIndexPosition();
	const int32 OldYIndex = EntityPawn->GetYIndexPosition();
	Grid[OldXIndex][OldYIndex]->SetEntityPawn(nullptr);
	
	ABNPanelActor* PanelActor = Grid[NewXIndex][NewYIndex];
	PanelActor->SetEntityPawn(EntityPawn);
	
	const FVector NewLocation = PanelActor->GetActorLocation();
	EntityPawn->SetActorLocation(NewLocation);
	EntityPawn->SetNewXIndexPosition(NewXIndex);
	EntityPawn->SetNewYIndexPosition(NewYIndex);
}

void ABNGridActor::SpawnPanel(const int32 XIndex, const int32 YIndex)
{
	const FVector Location(XIndex * PanelSpacingWidth, YIndex * PanelSpacingHeight, 0);
	const FRotator Rotation;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	UWorld* World = GetWorld();

	ABNPanelActor* NewPanelActor = World->SpawnActor<ABNPanelActor>(PanelActorSubclass, Location, Rotation, SpawnParameters);
	if (XIndex <= GridDividerIndex)
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


