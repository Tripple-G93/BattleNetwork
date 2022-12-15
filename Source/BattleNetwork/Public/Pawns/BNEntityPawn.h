// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BNBasePawn.h"
#include "Structs/BNStructs.h"
#include "Tables/BNFlipbookAnimationTable.h"
#include "BNEntityPawn.generated.h"

class ABNGridActor;
class UBoxComponent;
class UBNEntityWidgetSceneComponent;
class UDataTable;
class UPaperFlipbookComponent;
class USceneComponent;

UCLASS()
class BATTLENETWORK_API ABNEntityPawn : public ABNBasePawn
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> FlipbookAnimationDataTable;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBNEntityWidgetSceneComponent> EntityWidgetSceneComponent;

	UPROPERTY(Replicated)
	TObjectPtr<ABNGridActor> GridActorReference;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;
	
	UPROPERTY(ReplicatedUsing = OnRep_UpdateClientLocation)
	FBNGridLocation ServerGridLocation;

	TObjectPtr<FBNFlipbookAnimationTableInfoRow> CurrentFlipbookAnimationTableInfoRow;

	UPROPERTY(Replicated)
	FGameplayTag TeamTag;

	UPROPERTY()
	bool bCanMove;

public:

	ABNEntityPawn(const FObjectInitializer& ObjectInitializer);

	void FlipEntity();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void UpdateAnimation(FGameplayTag AnimationTag);
	
	/*
	 * Setters
	 */

	void SetGridActorReference(ABNGridActor* GridActor);
	
	void SetTeamTag(FGameplayTag NewTeamTag);
	
	void SetServerGridLocation(FBNGridLocation NewServerGridLocation);

	/*
	 * Getters
	 */

	FGameplayTag GetTeamTag() const;
	
	FBNGridLocation GetServerGridLocation() const;

	TObjectPtr<UPaperFlipbookComponent> GetPaperFlipbookComponent();

protected:

	virtual void BeginPlay() override;

	virtual void InitializeAttributes() override;
	
	void EnableMovementIfStandaloneMode();

	UFUNCTION()
	void UpdateIdleAnimation();

	UFUNCTION()
	void ClientCallMoveEntityLeftRPC();

	UFUNCTION()
	void ClientCallMoveEntityRightRPC();

	UFUNCTION()
	void ClientCallMoveEntityUpRPC();

	UFUNCTION()
	void ClientCallMoveEntityDownRPC();

	/*
	 * Server
	 */

	UFUNCTION(Server, Unreliable)
	void UpdateMoveAnimationRPC();
	
	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityLeftRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityRightRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityUpRPC();

	UFUNCTION(Server, Reliable, WithValidation)
	void MoveEntityDownRPC();
	
	/*
	 * OnRep_Notify
	 */

	UFUNCTION()
	void OnRep_UpdateClientLocation();
};
