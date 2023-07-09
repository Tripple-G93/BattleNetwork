// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNProjectilePool.h"

#include "Actors/BNProjectile.h"
#include "Tables/BNSpawnProjectileTable.h"

#include <Engine/World.h>

ABNProjectilePool::ABNProjectilePool()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABNProjectilePool::CreateProjectile(FGameplayTag projectileTypeGameplayTag, FVector SpawnLocation, FGameplayTag TeamGameplayTag, FGameplayEffectSpecHandle NewGameplayEffectSpecHandle)
{
    ABNProjectile* currentProjectile = FirstAvailableProjectiles[projectileTypeGameplayTag];
	if(currentProjectile != nullptr)
	{
        currentProjectile->SetActorHiddenInGame(false);
        currentProjectile->SetActorLocation(SpawnLocation);
        currentProjectile->SetProjectilesVelocity(TeamGameplayTag);
        currentProjectile->SetGameplayEffectSpecHandle(NewGameplayEffectSpecHandle);

        FirstAvailableProjectiles[projectileTypeGameplayTag] = currentProjectile->GetNextNextAvailableProjectile();
        currentProjectile->SetNextAvailableProjectile(nullptr);
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

	SpawnProjectiles();

	LinkProjectiles();
}

void ABNProjectilePool::SpawnProjectiles()
{
    TArray<FBNSpawnProjectileTableInfoRow*> DataRows;
    SpawnProjectileDataTable->GetAllRows<FBNSpawnProjectileTableInfoRow>("", DataRows);
    for (FBNSpawnProjectileTableInfoRow* DataRow : DataRows)
    {
        FGameplayTag ProjectileTypeGameplayTag = DataRow->ProjectileTypeGameplayTag;
        TSubclassOf<ABNProjectile> ProjectileClass = DataRow->ProjectileClass;
        int32 PoolSize = DataRow->SpawnAmount;
        Projectiles.Add(ProjectileTypeGameplayTag, TArray<ABNProjectile*>());
        Projectiles[ProjectileTypeGameplayTag].Reserve(PoolSize);
        for (int32 i = 0; i < PoolSize; ++i)
        {
            FVector Location(100.f * i, 0.f, 0.f);
            FRotator Rotation(0.f, 0.0f, 0.f);
            FVector Scale(1.f, 1.f, 1.f);
            FTransform SpawnTransform(Rotation, Location, Scale);

            FActorSpawnParameters SpawnParameters;
            SpawnParameters.Owner = this;
            UWorld* World = GetWorld();

            Projectiles[ProjectileTypeGameplayTag].Add(World->SpawnActor<ABNProjectile>(ProjectileClass, SpawnTransform, SpawnParameters));
            Projectiles[ProjectileTypeGameplayTag][i]->SetProjectileTypeGameplayTag(ProjectileTypeGameplayTag);
            Projectiles[ProjectileTypeGameplayTag][i]->SetActorHiddenInGame(true);
        }
    }
}

void ABNProjectilePool::LinkProjectiles()
{
    TArray<FBNSpawnProjectileTableInfoRow*> DataRows;
    SpawnProjectileDataTable->GetAllRows<FBNSpawnProjectileTableInfoRow>("", DataRows);
    for (FBNSpawnProjectileTableInfoRow* DataRow : DataRows)
    {
        FGameplayTag ProjectileTypeGameplayTag = DataRow->ProjectileTypeGameplayTag;

        FirstAvailableProjectiles.Add(ProjectileTypeGameplayTag, Projectiles[ProjectileTypeGameplayTag][0]);
        FirstAvailableProjectiles[ProjectileTypeGameplayTag]->MarkProjectileInObjectPool();

        int32 poolSize = DataRow->SpawnAmount;
        for (int32 i = 0; i < poolSize - 1; ++i)
        {
            Projectiles[ProjectileTypeGameplayTag][i]->SetNextAvailableProjectile(Projectiles[ProjectileTypeGameplayTag][i + 1]);
            Projectiles[ProjectileTypeGameplayTag][i]->MarkProjectileInObjectPool();
        }

        Projectiles[ProjectileTypeGameplayTag][Projectiles[ProjectileTypeGameplayTag].Max() - 1]->SetNextAvailableProjectile(nullptr);
    }
}

void ABNProjectilePool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateObjectPool();
}

void ABNProjectilePool::UpdateObjectPool()
{
    for (auto& ProjectilePair : Projectiles)
    {
        for (ABNProjectile* Projectile : ProjectilePair.Value)
        {
            if (Projectile->DoesProjectileNeedToBeAddedToTheObjectPool())
            {
                FGameplayTag ProjectileTypeGameplayTag = Projectile->GetProjectileTypeGameplayTag();
                Projectile->SetNextAvailableProjectile(FirstAvailableProjectiles[ProjectileTypeGameplayTag]);
                FirstAvailableProjectiles[ProjectileTypeGameplayTag] = Projectile;
                Projectile->MarkProjectileInObjectPool();
            }
        }
    }
}

