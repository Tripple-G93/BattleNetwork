// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNAIEntityPawn.h"

#include "ActorComponents/BNAbilitySystemComponent.h"
#include "Attributes/BNBaseAttributeSet.h"
#include "Controllers/BNEnemyAIController.h"

ABNAIEntityPawn::ABNAIEntityPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    HardRefenceAbilitySystemComponent = CreateDefaultSubobject<UBNAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    HardRefenceAbilitySystemComponent->SetIsReplicated(true);

    // Minimal Mode means that no GameplayEffects will replicate. They will only live on the Server. Attributes, GameplayTags, and GameplayCues will still replicate to us.
    HardRefenceAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    AbilitySystemComponent = HardRefenceAbilitySystemComponent;

    // Create the attribute set, this replicates by default
    // Adding it as a subobject of the owning actor of an AbilitySystemComponent
    // automatically registers the AttributeSet with the AbilitySystemComponent
    HardRefenceBaseAttributeSet = CreateDefaultSubobject<UBNBaseAttributeSet>(TEXT("BaseAttributeSet"));

    // Set our parent's TWeakObjectPtr
    AttributeSetBase = HardRefenceBaseAttributeSet;

    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;
}

void ABNAIEntityPawn::StartBehaviorTree()
{
     ABNEnemyAIController* EnemyAIController = Cast<ABNEnemyAIController>(GetController());
     if (ensure(EnemyAIController))
     {
         EnemyAIController->StartBehaviorTree();
     }
}

void ABNAIEntityPawn::StopBehaviorTree()
{
    ABNEnemyAIController* EnemyAIController = Cast<ABNEnemyAIController>(GetController());
    if (ensure(EnemyAIController))
    {
        EnemyAIController->StopBehaviorTree();
    }
}

void ABNAIEntityPawn::BeginPlay()
{
    Super::BeginPlay();

    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
        InitializeAttributes();
        AddStartupEffects();
        AddCharacterAbilities();       
    }
}
