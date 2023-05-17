// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GameplayTagContainer.h>
#include "BNGridActor.generated.h"

class ABNEntityPawn;
class ABNEntitySpawnerActor;
class ABNPanelActor;
class ABNPlayerPawn;
class UCameraComponent;
class USceneComponent;
class USpringArmComponent;

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

	UPROPERTY(EditDefaultsOnly, Category = "BN|Class References")
	TSubclassOf<ABNPanelActor> PanelActorSubclass;

    UPROPERTY(EditDefaultsOnly, Category = "BN|Class References")
    TSubclassOf<ABNEntitySpawnerActor> EntitySpawnerActorClass;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

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

    UPROPERTY(EditDefaultsOnly, Category = "BN|Gameplay Tags")
    FGameplayTag Team1Tag;

    UPROPERTY(EditDefaultsOnly, Category = "BN|Gameplay Tags")
    FGameplayTag Team2Tag;

    UPROPERTY(EditDefaultsOnly, Category = "BN|Gameplay Tags")
	FGameplayTag PlayerEntityTag;

    ABNEntitySpawnerActor* EntitySpawnerActor;
	
public:	

	ABNGridActor(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void InitializeGrid();

	bool CanEntityMoveLeft(const ABNEntityPawn* EntityPawn);

	bool CanEntityMoveRight(const ABNEntityPawn* EntityPawn);

	bool CanEntityMoveUp(const ABNEntityPawn* EntityPawn);

	bool CanEntityMoveDown(const ABNEntityPawn* EntityPawn);

	void MoveEntityToNewPanel(ABNEntityPawn* EntityPawn, int32 NewXIndex, int32 NewYIndex);

	float GetLeftMostPanelXLocation();

	float GetRightMostPanelXLocation();

    ABNEntityPawn* CreateEntity(FGameplayTag EntityTypeTag, int XGridPosition, int YGridPosition);
	
protected:
	
    void CreateGrid();

    void CreateEntitySpawner();

    void SpawnEntities();

	void SpawnPanel(const int32 XIndex, const int32 YIndex);

};
