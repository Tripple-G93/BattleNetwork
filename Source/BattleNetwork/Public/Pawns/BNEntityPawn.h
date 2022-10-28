// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/BNBasePawn.h"
#include "Structs/BNStructs.h"
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
	
	UPROPERTY(ReplicatedUsing = OnRep_UpdateClientLocation)
	FBNGridLocation ServerGridLocation;

	UPROPERTY(Replicated)
	FGameplayTag TeamTag;

	UPROPERTY()
	bool bCanMove;

public:

	ABNEntityPawn(const FObjectInitializer& ObjectInitializer);

	void FlipEntity() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
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

protected:

	virtual void BeginPlay() override;

	void EnableMovementIfStandaloneMode();

	UFUNCTION()
	void UpdateAnimation();

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
