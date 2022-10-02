// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "Tables/BNFlipbookAnimationTable.h"
#include "BNBasePawn.generated.h"

class UAbilitySystemComponent;
class UBNAbilitySystemComponent;
class UDataTable;
class UPaperFlipbookComponent;

UCLASS()
class BATTLENETWORK_API ABNBasePawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> FlipbookAnimationDataTable;

	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASShooter|Abilities")
	//TArray<TSubclassOf<class UGSGameplayAbility>> CharacterAbilities;

	// Reference to the ASC. It will live on the PlayerState or here if the character doesn't have a PlayerState.
	UPROPERTY()
	UBNAbilitySystemComponent* AbilitySystemComponent;
	
	TObjectPtr<FBNFlipbookAnimationTableInfoRow> CurrentFlipbookAnimationTableInfoRow;
	
public:

	ABNBasePawn(const FObjectInitializer& ObjectInitializer);

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// RemoveCharacterAbilities

	// AddCharacterAbilities In protected
protected:

	void UpdateAnimation(FGameplayTag NewStatus);
	
	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();
};
