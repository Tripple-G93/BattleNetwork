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

void ABNProjectilePool::CreateProjectile(FVector SpawnLocation, FGameplayTag TeamGameplayTag, FBNGridLocation GridLocation, FGameplayEffectSpecHandle NewGameplayEffectSpecHandle)
{
	// TODO BN: Possible pass in the damage comming from the attribute of the entity that shot it and set it in the game spec?
	FirstAvailableProjectile->SetActorHiddenInGame(false);
	FirstAvailableProjectile->SetActorLocation(SpawnLocation);
	FirstAvailableProjectile->SetProjectilesVelocity(TeamGameplayTag);
	FirstAvailableProjectile->SetGameplayEffectSpecHandle(NewGameplayEffectSpecHandle);
	
	// TODO: Handle the "spawning" and "unspawning" of the projectiles
	//FirstAvailableProjectile = FirstAvailableProjectile->GetNextNextAvailableProjectile();
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

// Called every frame
void ABNProjectilePool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

