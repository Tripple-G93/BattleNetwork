// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNASCActor.h"
#include "ActorComponents/BNAbilitySystemComponent.h"

// Sets default values
ABNASCActor::ABNASCActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	// Create ability system component, and set it to be explicitly replicated
	AbilitySystemComponent = CreateDefaultSubobject<UBNAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Minimal mode means GameplayEffects are not replicated to anyone. Only GameplayTags and Attributes are replicated to clients.
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

// Called when the game starts or when spawned
void ABNASCActor::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ABNASCActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

