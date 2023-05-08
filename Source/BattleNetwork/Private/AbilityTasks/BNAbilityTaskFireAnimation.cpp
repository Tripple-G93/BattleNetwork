// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/BNAbilityTaskFireAnimation.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Pawns/BNEntityPawn.h"

UBNAbilityTaskFireAnimation::UBNAbilityTaskFireAnimation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

UBNAbilityTaskFireAnimation* UBNAbilityTaskFireAnimation::PlayFlipBookFireAnimationAndWaitForEvent(UGameplayAbility* OwningAbility, FName TaskInstanceName, FGameplayTag NewFireFlipBookAnimationTag)
{
    UBNAbilityTaskFireAnimation* abilityTaskFireAnimation = NewAbilityTask<UBNAbilityTaskFireAnimation>(OwningAbility, TaskInstanceName);
    abilityTaskFireAnimation->FireFlipBookAnimationTag = NewFireFlipBookAnimationTag;

    return abilityTaskFireAnimation;
}

void UBNAbilityTaskFireAnimation::Activate()
{
    if (AbilitySystemComponent->IsValidLowLevel())
    {
        const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
        ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->AvatarActor);
        if (ensure(EntityPawn))
        {
            EntityPawn->UpdateAnimation(FireFlipBookAnimationTag);

            UPaperFlipbookComponent* PaperFlipbookComponent = EntityPawn->GetPaperFlipbookComponent();
            PaperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UBNAbilityTaskFireAnimation::BoradCastComplete);
            // We want to set up a binding for when the paper 2d animation has finished
                // So we go ahead and fire up the completed event. 
            // We want to find out how long it takes to run one UPaperSprite within the Paper 2D
            // We then want to start the animation for the paper 2d component
            // After that we will start the timer to run with that value we got at the beginning
            // We will update the timer for when there are variable frames for the sprite (Some last longer than others)
                // We will check to see if that sprite has a socket and if it does
                // We close the timer and also fire the event of the socket location to fire off the projectile
        }
    }
    // Here we will need to get the flip book component bind it to know when it ends and when we move onto the next animation.
    // When we have it with the socket then we want to fire off the event for that
}

void UBNAbilityTaskFireAnimation::BoradCastComplete()
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnCompleted.Broadcast(FTransform());
    }

    EndTask();
}
