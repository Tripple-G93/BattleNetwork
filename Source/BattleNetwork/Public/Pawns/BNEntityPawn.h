// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BNBasePawn.h"
#include "BNEntityPawn.generated.h"

class ABNGridActor;
class UDataTable;
class UPaperFlipbookComponent;
class USceneComponent;

UCLASS()
class BATTLENETWORK_API ABNEntityPawn : public ABNBasePawn
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UDataTable> FlipbookAnimationDataTable;
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(Replicated)
	TObjectPtr<ABNGridActor> GridActorReference;
	
	UPROPERTY(Replicated)
	int32 XIndex;

	UPROPERTY(Replicated)
	int32 YIndex;

	UPROPERTY(Replicated)
	FGameplayTag TeamTag;

	FTimerHandle EnableEntityMovementTimerHandler;
	
	bool bCanNotMove;

public:

	ABNEntityPawn(const FObjectInitializer& ObjectInitializer);

	void FlipEntity() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/*
	 * Setters
	 */

	void SetGridActorReference(ABNGridActor* GridActor);
	
	void SetTeamTag(FGameplayTag NewTeamTag);
	
	void SetNewXIndexPosition(const int32 NewXIndex);
	void SetNewYIndexPosition(const int32 NewYIndex);

	/*
	 * Getters
	 */
	int32 GetXIndexPosition() const;
	int32 GetYIndexPosition() const;

	FGameplayTag GetTeamTag() const;

protected:

	virtual void BeginPlay() override;

	void DisableEntityMovement();
	void EnableEntityMovement();

	/*
	 * Server
	 */

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityLeftRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityRightRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityUpRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityDownRPC();
};
