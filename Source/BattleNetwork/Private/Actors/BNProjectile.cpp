// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
ABNProjectile::ABNProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
	SetReplicateMovement(true);

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	PaperFlipbookComponent = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);

	SphereCollisionBox = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComponent"));
	SphereCollisionBox->SetupAttachment(PaperFlipbookComponent);
	
	ProjectileMovementComponent = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovementComponent"));

	NextAvailableProjectile = nullptr;

}

// Called when the game starts or when spawned
void ABNProjectile::BeginPlay()
{
	Super::BeginPlay();

	/* TODO BN: We want to create the damage effect spec handle so that we can be able to apply the damage on collision
	FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());
		
	// Pass the damage to the Damage Execution Calculation through a SetByCaller value on the GameplayEffectSpec
	DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);
	*/
}

// Called every frame
void ABNProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABNProjectile::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);
}

ABNProjectile* ABNProjectile::GetNext() const
{
	return NextAvailableProjectile;
}

void ABNProjectile::SetNextAvailableProjectile(ABNProjectile* Projectile)
{
	NextAvailableProjectile = Projectile;
}

