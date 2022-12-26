// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNProjectilePool.h"
#include "Actors/BNProjectile.h"
#include "Engine/World.h"

// Sets default values
ABNProjectilePool::ABNProjectilePool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstAvailableProjectile = nullptr;
	PoolSize = 0;
}

void ABNProjectilePool::CreateProjectile(FVector SpawnLocation, FGameplayTag TeamGameplayTag, FGameplayEffectSpecHandle NewGameplayEffectSpecHandle)
{
	if(FirstAvailableProjectile != nullptr)
	{
		ABNProjectile* CurrentProjectile = FirstAvailableProjectile;
		CurrentProjectile->SetActorHiddenInGame(false);
		CurrentProjectile->SetActorLocation(SpawnLocation);
		CurrentProjectile->SetProjectilesVelocity(TeamGameplayTag);
		CurrentProjectile->SetGameplayEffectSpecHandle(NewGameplayEffectSpecHandle);

		FirstAvailableProjectile = CurrentProjectile->GetNextNextAvailableProjectile();
		CurrentProjectile->SetNextAvailableProjectile(nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Your trying to spawn a projectile when none are in the pool!"));
	}
}

// Called when the game starts or when spawned
void ABNProjectilePool::BeginPlay()
{
	Super::BeginPlay();

	if(ensure(ProjectileClass) && PoolSize > 0)
	{
		SpawnProjectiles();

		LinkProjectiles();
	}
}

void ABNProjectilePool::SpawnProjectiles()
{
	Projectiles.Reserve(PoolSize);
	for(int i = 0; i < PoolSize; ++i)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;
		UWorld* World = GetWorld();

		Projectiles.Add(World->SpawnActor<ABNProjectile>(ProjectileClass, SpawnParameters));
		Projectiles[i]->SetActorHiddenInGame(true);
	}
}

void ABNProjectilePool::LinkProjectiles()
{
	FirstAvailableProjectile = Projectiles[0];
	Projectiles[PoolSize - 1]->SetNextAvailableProjectile(nullptr);

	for(int i = 0; i < PoolSize - 1; ++i)
	{
		Projectiles[i]->SetNextAvailableProjectile(Projectiles[i+1]);
	}
}

void ABNProjectilePool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateObjectPool();
}

void ABNProjectilePool::UpdateObjectPool()
{
	for(int i = 0; i < PoolSize; ++i)
	{
		if(Projectiles[i]->DoesProjectileNeedToBeAddedToTheObjectPool())
		{
			Projectiles[i]->SetNextAvailableProjectile(FirstAvailableProjectile);
			FirstAvailableProjectile = Projectiles[i];
			FirstAvailableProjectile->MarkProjectileInObjectPool();
		}
	}
}

