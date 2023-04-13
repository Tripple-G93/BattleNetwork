// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/BNGridActor.h"

#include "Actors/BNEntitySpawnerActor.h"
#include "AbilitySystemComponent.h"
#include "Actors/BNPanelActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Net/UnrealNetwork.h"
#include "Pawns/BNPlayerPawn.h"

// Sets default values
ABNGridActor::ABNGridActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true; 
	
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	SpringArmComponent = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SceneComponent);
	
	CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	GridWidth = 6;
	GridHeight = 3;

	GridDividerIndex = 2;

	PanelSpacingWidth = 24;
	PanelSpacingHeight = 40;
}

void ABNGridActor::InitializeGrid()
{
    CreateEntitySpawner();

    SpawnEntities();

    CreateGrid();
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

void ABNGridActor::CreateEntitySpawner()
{
    if (ensure(EntitySpawnerActorClass))
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = this;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        EntitySpawnerActor = GetWorld()->SpawnActor<ABNEntitySpawnerActor>(EntitySpawnerActorClass, SpawnParameters);
    }
}

void ABNGridActor::SpawnEntities()
{
    if (ensure(EntitySpawnerActor))
    {
        EntitySpawnerActor->SpawnEntities();
    }
}

void ABNGridActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABNGridActor, Grid);
}

bool ABNGridActor::CanEntityMoveLeft(const ABNEntityPawn* EntityPawn)
{
	const FBNGridLocation GridLocation = EntityPawn->GetServerGridLocation();
	
	const int32 XIndex = GridLocation.XIndex;
	const int32 YIndex = GridLocation.YIndex;
	
	if(EntityPawn->GetTeamTag() == FGameplayTag::RequestGameplayTag(Team1Tag))
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
	const FBNGridLocation GridLocation = EntityPawn->GetServerGridLocation();
	
	const int32 XIndex = GridLocation.XIndex;
	const int32 YIndex = GridLocation.YIndex;

	if(EntityPawn->GetTeamTag() == FGameplayTag::RequestGameplayTag(Team1Tag))
	{
		return XIndex < GridDividerIndex && Grid[XIndex + 1][YIndex]->GetEntityPawn() == nullptr;
	}
	else
	{
		return XIndex < GridWidth - 1 && Grid[XIndex + 1][YIndex]->GetEntityPawn() == nullptr;
	}
}

bool ABNGridActor::CanEntityMoveUp(const ABNEntityPawn* EntityPawn)
{
	const FBNGridLocation GridLocation = EntityPawn->GetServerGridLocation();
	
	const int32 XIndex = GridLocation.XIndex;
	const int32 YIndex = GridLocation.YIndex;
	
	return YIndex < GridHeight - 1 && Grid[XIndex][YIndex + 1]->GetEntityPawn() == nullptr; 
}

bool ABNGridActor::CanEntityMoveDown(const ABNEntityPawn* EntityPawn)
{
	const FBNGridLocation GridLocation = EntityPawn->GetServerGridLocation();
	
	const int32 XIndex = GridLocation.XIndex;
	const int32 YIndex = GridLocation.YIndex;

	return YIndex > 0 && Grid[XIndex][YIndex - 1]->GetEntityPawn() == nullptr;
}

void ABNGridActor::MoveEntityToNewPanel(ABNEntityPawn* EntityPawn, int32 NewXIndex, int32 NewYIndex)
{
	// TODO BN: This check exist because of spawning and replication issues at the beginning of the game remove when fixed
	ABNPanelActor* PanelActor = Grid[NewXIndex][NewYIndex];
	if(PanelActor)
	{
		const FBNGridLocation GridLocation = EntityPawn->GetServerGridLocation();
	
		const int32 OldXIndex = GridLocation.XIndex;
		const int32 OldYIndex = GridLocation.YIndex;
		Grid[OldXIndex][OldYIndex]->SetEntityPawn(nullptr);
	
		PanelActor->SetEntityPawn(EntityPawn);
	
		const FVector NewLocation = PanelActor->GetActorLocation();
		EntityPawn->SetActorLocation(NewLocation + EntityPawn->GetSpriteOffset());
	
		EntityPawn->SetServerGridLocation(FBNGridLocation(NewXIndex, NewYIndex));
	}
}

float ABNGridActor::GetLeftMostPanelXLocation()
{
	return Grid[0][0]->GetActorLocation().X - PanelSpacingWidth;
}

float ABNGridActor::GetRightMostPanelXLocation()
{
	return Grid[GridWidth - 1][0]->GetActorLocation().X + PanelSpacingWidth;	
}

ABNEntityPawn* ABNGridActor::CreateEntity(FGameplayTag EntityTypeTag, int XGridPosition, int YGridPosition)
{
    ABNPanelActor* Panel = Grid[XGridPosition][YGridPosition];
    const FVector Location = Panel->GetActorLocation();

    ABNEntityPawn* entityPawn = EntitySpawnerActor->GetEntityFromSpawner(EntityTypeTag);
    entityPawn->SetActorHiddenInGame(false);
    entityPawn->SetActorLocation(Location + entityPawn->GetSpriteOffset());

    FRotator Rotation;
    if (XGridPosition >= GridWidth / 2)
    {
        entityPawn->SetTeamTag(Team2Tag);
        Rotation.Yaw = 180;
    }
    else
    {
        entityPawn->SetTeamTag(Team1Tag);
    }

    entityPawn->SetActorRotation(Rotation);

    Panel->SetEntityPawn(entityPawn);

    entityPawn->SetServerGridLocation(FBNGridLocation(XGridPosition, YGridPosition));

    return entityPawn;
}

void ABNGridActor::SpawnPanel(const int32 XIndex, const int32 YIndex)
{
	const FVector Location(XIndex * PanelSpacingWidth, 0, YIndex * PanelSpacingHeight);
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


