// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "Structs/BNStructs.h"
#include "BNProjectile.generated.h"

class UGameplayEffect;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USceneComponent;
class USphereComponent;

UCLASS()
class BATTLENETWORK_API ABNProjectile : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category="BN|Values")
	TObjectPtr<UGameplayEffect> GameplayEffect;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereCollisionBox;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	TObjectPtr<ABNProjectile> NextAvailableProjectile;
	
public:	

	ABNProjectile(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetActorHiddenInGame(bool bNewHidden) override;

	ABNProjectile* GetNextNextAvailableProjectile() const;
	void SetNextAvailableProjectile(ABNProjectile* Projectile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
