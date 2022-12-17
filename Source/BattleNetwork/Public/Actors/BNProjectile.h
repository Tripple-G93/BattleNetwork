// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffect.h"
#include "BNProjectile.generated.h"

class ABNProjectile;
class UCapsuleComponent;
class UGameplayEffect;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USceneComponent;

DECLARE_DELEGATE_OneParam(FOnProjectileDeactivateSignature, ABNProjectile*);

UCLASS()
class BATTLENETWORK_API ABNProjectile : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category="BN|Values")
	FVector ProjectileVelocity;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> SceneComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> PaperFlipbookComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCapsuleComponent> CollisionCapsuleComponent;

	UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	TObjectPtr<ABNProjectile> NextAvailableProjectile;

	FGameplayTag TeamFiredGameplayTag;

	FGameplayEffectSpecHandle GameplayEffectSpecHandle;
	
public:	

	FOnProjectileDeactivateSignature OnProjectileDeactivateDelegate;
	ABNProjectile(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;
	
	virtual void SetActorHiddenInGame(bool bNewHidden) override;

	void SetProjectilesVelocity(FGameplayTag GameplayTag);

	void SetTeamFiredTag(FGameplayTag NewTeamFiredGameplayTag);

	void SetGameplayEffectSpecHandle(FGameplayEffectSpecHandle NewGameplayEffectSpecHandle);
	
	ABNProjectile* GetNextNextAvailableProjectile() const;
	void SetNextAvailableProjectile(ABNProjectile* Projectile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	void ResetProjectileLocation();

	// Has to be a server call only since the grid actor exist only in the server
	bool CanWeTurnOffProjectile() const;
};
