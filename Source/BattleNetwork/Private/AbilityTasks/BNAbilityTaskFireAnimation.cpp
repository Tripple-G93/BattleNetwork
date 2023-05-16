// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/BNAbilityTaskFireAnimation.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "Pawns/BNEntityPawn.h"

UBNAbilityTaskFireAnimation* UBNAbilityTaskFireAnimation::PlayFlipBookFireAnimationAndWaitForEvent(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayTag NewFireFlipBookAnimationTag, FName NewPaperSpriteSocketName)
{
    UBNAbilityTaskFireAnimation* abilityTaskFireAnimation = NewAbilityTask<UBNAbilityTaskFireAnimation>(OwningAbility, TaskInstanceName);
    abilityTaskFireAnimation->FireFlipBookAnimationTag = NewFireFlipBookAnimationTag;
    abilityTaskFireAnimation->PaperSpriteSocketName = NewPaperSpriteSocketName;

    return abilityTaskFireAnimation;
}

void UBNAbilityTaskFireAnimation::Activate()
{
    if (AbilitySystemComponent->IsValidLowLevel())
    {
        ABNEntityPawn* EntityPawn = GetEntityPawn();
        if (ensure(EntityPawn))
        {
            EntityPawn->UpdateAnimation(FireFlipBookAnimationTag);

            // We want to get our own custom paper flip book so we can bind to the socket transform location to then fire off the projectile
            // Once we have received the message similar to what we were trying to do before with the separate fire projectile and complete function
            UPaperFlipbookComponent* paperFlipbookComponent = EntityPawn->GetPaperFlipbookComponent();
            SetBulletSpawnLocation(paperFlipbookComponent);
            paperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UBNAbilityTaskFireAnimation::BroadCastComplete);
            paperFlipbookComponent->PlayFromStart();
        }
    }
}

void UBNAbilityTaskFireAnimation::BroadCastComplete()
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        ABNEntityPawn* EntityPawn = GetEntityPawn();
        if (ensure(EntityPawn))
        {
            UPaperFlipbookComponent* paperFlipbookComponent = EntityPawn->GetPaperFlipbookComponent();
            paperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &UBNAbilityTaskFireAnimation::BroadCastComplete);

            OnCompleted.Broadcast(BulletSpawnLocation);
        }
    }

    EndTask();
}

void UBNAbilityTaskFireAnimation::SetBulletSpawnLocation(UPaperFlipbookComponent* PaperFlipBookComponent)
{
    for (int i = 0; i < PaperFlipBookComponent->GetFlipbookLengthInFrames(); ++i)
    {
        if (PaperFlipBookComponent->GetFlipbook()->FindSocket(PaperSpriteSocketName, i, BulletSpawnLocation))
        {
            BulletSpawnLocation *= PaperFlipBookComponent->GetComponentTransform();
            break;
        }
    }
}

ABNEntityPawn* UBNAbilityTaskFireAnimation::GetEntityPawn()
{
    const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
    ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->AvatarActor);
    return EntityPawn;
}
