// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/BNAbilityTaskFireAnimation.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "ActorComponents/BNPaperFlipbookComponent.h"
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
            UBNPaperFlipbookComponent* PaperFlipbookComponent = EntityPawn->GetBNPaperFlipbookComponent();
            PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UBNAbilityTaskFireAnimation::BroadCastComplete);
            PaperFlipbookComponent->OnFoundSocket.AddDynamic(this, &UBNAbilityTaskFireAnimation::BroadCastFireProjectile);
            PaperFlipbookComponent->SocketToLookFor(PaperSpriteSocketName);
            PaperFlipbookComponent->PlayFromStart();
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
            UBNPaperFlipbookComponent* paperFlipbookComponent = EntityPawn->GetBNPaperFlipbookComponent();
            paperFlipbookComponent->OnFinishedPlaying.RemoveDynamic(this, &UBNAbilityTaskFireAnimation::BroadCastComplete);
            paperFlipbookComponent->OnFoundSocket.RemoveDynamic(this, &UBNAbilityTaskFireAnimation::BroadCastFireProjectile);

            OnCompleted.Broadcast();
        }
    }

    EndTask();
}

void UBNAbilityTaskFireAnimation::BroadCastFireProjectile(FTransform BulletSpawnLocation)
{
    OnFireProjectile.Broadcast(BulletSpawnLocation);
}

ABNEntityPawn* UBNAbilityTaskFireAnimation::GetEntityPawn()
{
    const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
    ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->AvatarActor);
    return EntityPawn;
}
