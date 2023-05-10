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

            UPaperFlipbookComponent* paperFlipbookComponent = EntityPawn->GetPaperFlipbookComponent();
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

            FTransform projectileTransform = paperFlipbookComponent->GetSocketTransform(PaperSpriteSocketName);
            OnCompleted.Broadcast(projectileTransform);
        }
    }

    EndTask();
}

ABNEntityPawn* UBNAbilityTaskFireAnimation::GetEntityPawn()
{
    const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
    ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->AvatarActor);
    return EntityPawn;
}
