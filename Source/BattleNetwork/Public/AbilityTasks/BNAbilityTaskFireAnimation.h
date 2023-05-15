// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "BNAbilityTaskFireAnimation.generated.h"

class ABNEntityPawn;
class UPaperFlipbookComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBNAbilityTaskFireAnimation, FTransform, BulletSpawnLocation);

/**
 * 
 */
UCLASS()
class BATTLENETWORK_API UBNAbilityTaskFireAnimation : public UAbilityTask
{
	GENERATED_BODY()
	
public:

    FBNAbilityTaskFireAnimation OnCompleted;

    FBNAbilityTaskFireAnimation OnFireProjectile;

protected:

    FGameplayTag FireFlipBookAnimationTag;

    FName PaperSpriteSocketName;

    FTransform BulletSpawnLocation;

public:

    static UBNAbilityTaskFireAnimation* PlayFlipBookFireAnimationAndWaitForEvent(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayTag NewFireFlipBookAnimationTag, FName NewPaperSpriteSocketName);

    virtual void Activate() override;

protected:

    UFUNCTION()
    void BroadCastComplete();

    void SetBulletSpawnLocation(UPaperFlipbookComponent* PaperFlipBookComponent);

    ABNEntityPawn* GetEntityPawn();

};
