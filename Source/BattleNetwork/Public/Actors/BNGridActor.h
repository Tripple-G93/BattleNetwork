// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pawns/BNPlayerPawn.h"
#include "BNGridActor.generated.h"

class ABNEntityPawn;
class ABNPanelActor;
class ABNPlayerPawn;
class UCameraComponent;
class USceneComponent;

USTRUCT()
struct FBNPannel2DArray {
	GENERATED_BODY()

public:

	UPROPERTY()
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
	TSubclassOf<ABNPanelActor> PanelActorSubclass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABNPlayerPawn> PlayerPawnSubclass;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(Replicated)
	TArray<FBNPannel2DArray> Grid;
	
	UPROPERTY(EditDefaultsOnly)
	int32 GridWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 GridHeight;

	UPROPERTY(EditDefaultsOnly)
	int32 GridDividerIndex;
	
	UPROPERTY(EditDefaultsOnly)
	int32 PanelSpacingWidth;

	UPROPERTY(EditDefaultsOnly)
	int32 PanelSpacingHeight;
	
	int32 PlayerSpawnOffset;
	
public:	

	ABNGridActor(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void CreateGrid();

	bool CanEntityMoveLeft(const ABNEntityPawn* EntityPawn);

	bool CanEntityMoveRight(const ABNEntityPawn* EntityPawn);

	void MoveEntityToNewPanel(ABNEntityPawn* EntityPawn, int32 NewXIndex, int32 NewYIndex);

	/*
     * Server Calls
     */
	
	UFUNCTION(Server, Reliable)
	void SpawnPlayer1(APlayerController* PlayerController);

	UFUNCTION(Server, Reliable)
	void SpawnPlayer2(APlayerController* PlayerController);
	
protected:
	
	void SpawnPanel(const int32 XIndex, const int32 YIndex);

};
