// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNBasePawn.h"
#include "Objects/BNUtilityStatics.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ABNBasePawn::ABNBasePawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PaperFlipbookComponent"));
}

UAbilitySystemComponent* ABNBasePawn::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ABNBasePawn::UpdateAnimation(FGameplayTag NewStatus)
{
	CurrentFlipbookAnimationTableInfoRow = UBNUtilityStatics::UpdateAnimation(FlipbookAnimationDataTable,
		CurrentFlipbookAnimationTableInfoRow, PaperFlipbookComponent, NewStatus);
}

void ABNBasePawn::AddCharacterAbilities()
{
	/*
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !IsValid(AbilitySystemComponent) || AbilitySystemComponent->bCharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UBNGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->bCharacterAbilitiesGiven = true;
	*/
}