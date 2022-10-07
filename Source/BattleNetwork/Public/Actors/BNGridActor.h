// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawns/BNPlayerPawn.h"
#include "BNGridActor.generated.h"

class ABNPanelActor;
class ABNPlayerPawn;

USTRUCT()
struct FBNPannel2DArray {
	GENERATED_BODY()

public:

	TArray<ABNPanelActor*> PannelArray;

	ABNPanelActor* operator[] (int32 index)
	{
		return PannelArray[index];
	}

	void Add(ABNPanelActor* PanelActor)
	{
		PannelArray.Add(PanelActor);
	}
};

UCLASS()
class BATTLENETWORK_API ABNGridActor : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABNPanelActor> PanelActor;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABNPlayerPawn> PlayerPawnSubclass;

	UPROPERTY(EditDefaultsOnly)
	int32 GridWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 GridHeight;

	UPROPERTY(EditDefaultsOnly)
	int32 PanelSpacingWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 PanelSpacingHeight;

	int32 PlayerSpawnOffset;

	TArray<FBNPannel2DArray> Grid;

	bool IsPlayer1Spawned;
	bool IsPlayer2Spawned;
	
public:	

	ABNGridActor();

	void SpawnPlayers(APlayerController* PlayerController);
protected:

	virtual void BeginPlay() override;
	
	void CreateGrid();
	void SpawnPanel(const int32 XIndex, const int32 YIndex);

};
