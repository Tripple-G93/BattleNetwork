// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "BNAbilityTaskFireAnimation.generated.h"

class ABNEntityPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBNAbilityTaskAnimationCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNAbilityTaskFireProjectile, FTransform, BulletSpawnLocation);

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNAbilityTaskFireAnimation : public UAbilityTask
{
	GENERATED_BODY()
	
public:

    FBNAbilityTaskAnimationCompleted OnCompleted;

    FBNAbilityTaskFireProjectile OnFireProjectile;

protected:

    FGameplayTag FireFlipBookAnimationTag;

    FName PaperSpriteSocketName;

public:

    static UBNAbilityTaskFireAnimation* PlayFlipBookFireAnimationAndWaitForEvent(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayTag NewFireFlipBookAnimationTag, FName NewPaperSpriteSocketName);

    virtual void Activate() override;

protected:

    UFUNCTION()
    void BroadCastComplete();

    UFUNCTION()
    void BroadCastFireProjectile(FTransform BulletSpawnLocation);

    ABNEntityPawn* GetEntityPawn();

};
