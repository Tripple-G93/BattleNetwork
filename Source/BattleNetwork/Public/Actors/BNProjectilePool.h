// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include <GameplayEffectTypes.h>
#include "BNProjectilePool.generated.h"

class ABNProjectile;

UCLASS()
class BATTLENETWORK_API ABNProjectilePool : public AActor
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditDefaultsOnly, Category="BN")
	TObjectPtr<UDataTable> SpawnProjectileDataTable;

    TMap<FGameplayTag, TArray<ABNProjectile*>> Projectiles;

    TMap<FGameplayTag, ABNProjectile*> FirstAvailableProjectiles;

public:

	// Sets default values for this actor's properties
	ABNProjectilePool();
	
	void CreateProjectile(FGameplayTag projectileTypeGameplayTag, FVector SpawnLocation, FGameplayTag TeamGameplayTag, FGameplayEffectSpecHandle NewGameplayEffectSpecHandle);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnProjectiles();

	void LinkProjectiles();

	void UpdateObjectPool();

};
