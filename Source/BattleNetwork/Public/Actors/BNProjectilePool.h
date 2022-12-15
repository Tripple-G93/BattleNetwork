// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "Structs/BNStructs.h"
#include "BNProjectilePool.generated.h"

class ABNProjectile;

UCLASS()
class BATTLENETWORK_API ABNProjectilePool : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditDefaultsOnly, Category="BN|ObjectPool")
	int32 PoolSize;

	UPROPERTY(EditDefaultsOnly, Category="BN|ObjectPool|Projectile")
	TSubclassOf<ABNProjectile> ProjectileClass;
	
	TArray<TObjectPtr<ABNProjectile>> Projectiles;

	TObjectPtr<ABNProjectile> FirstAvailableProjectile;

public:

	// Sets default values for this actor's properties
	ABNProjectilePool();
	
	void CreateProjectile(FVector SpawnLocation, FGameplayTag TeamGameplayTag, FBNGridLocation GridLocation, FGameplayEffectSpecHandle NewGameplayEffectSpecHandle);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnProjectiles();

	void LinkProjectiles();

};
