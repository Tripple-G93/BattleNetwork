// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNProjectilePool.h"
#include "Actors/BNProjectile.h"
#include "Engine/World.h"

// Sets default values
ABNProjectilePool::ABNProjectilePool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PoolSize = 0;
}

void ABNProjectilePool::CreateProjectile()
{
	// TODO BN: We want to initialize and turn on the projectile for it to be in use
}

// Called when the game starts or when spawned
void ABNProjectilePool::BeginPlay()
{
	Super::BeginPlay();

	SpawnProjectiles();
}

void ABNProjectilePool::SpawnProjectiles()
{
	if(ensure(ProjectileClass))
	{
		for(int i = 0; i < PoolSize; ++i)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;
			UWorld* World = GetWorld();

			Projectiles.Add(World->SpawnActor<ABNProjectile>(ProjectileClass, SpawnParameters));
			// TODO BN: Need to be able to set the next for each projectile so we always know what is the next available
		}
	}
	
}

// Called every frame
void ABNProjectilePool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

