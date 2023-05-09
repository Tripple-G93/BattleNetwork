// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTasks/BNAbilityTaskFireAnimation.h"
#include "ActorComponents/BNAbilitySystemComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "PaperSprite.h"
#include "Pawns/BNEntityPawn.h"

UBNAbilityTaskFireAnimation::UBNAbilityTaskFireAnimation(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

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

            // TODO: Use in its own function to get the frame duration
            UPaperFlipbookComponent* paperFlipbookComponent = EntityPawn->GetPaperFlipbookComponent();
            paperFlipbookComponent->OnFinishedPlaying.AddDynamic(this, &UBNAbilityTaskFireAnimation::BroadCastComplete);

            // We do not need to do this on the client side at all
            UPaperFlipbook* paperFlipbook = paperFlipbookComponent->GetFlipbook();
            
            float flipbookLength = paperFlipbook->GetTotalDuration();
            
            int32 numFrames = paperFlipbook->GetNumKeyFrames();
            
            float frameDuration = flipbookLength / static_cast<float>(numFrames);
            frameDuration *= paperFlipbookComponent->GetPlayRate();

            StartTimeForTimeHandle = GetWorld()->GetTimeSeconds();
            EntityPawn->GetWorldTimerManager().SetTimer(CheckPaperSocketTimerHandle, this, &UBNAbilityTaskFireAnimation::CheckForBulletLocationSocket, frameDuration, true);
        }
    }
}

void UBNAbilityTaskFireAnimation::OnDestroy(bool AbilityEnded)
{
    if (AbilityEnded)
    {
        ABNEntityPawn* EntityPawn = GetEntityPawn();
        if (ensure(EntityPawn))
        {
            EntityPawn->GetWorldTimerManager().ClearTimer(CheckPaperSocketTimerHandle);
        }
    }

    Super::OnDestroy(AbilityEnded);
}

// Change the name from bullet to projectile
void UBNAbilityTaskFireAnimation::CheckForBulletLocationSocket()
{
    ABNEntityPawn* EntityPawn = GetEntityPawn();
    if (ensure(EntityPawn))
    {
        UPaperFlipbookComponent* paperFlipbookComponent = EntityPawn->GetPaperFlipbookComponent();
        UPaperFlipbook* paperFlipbook = paperFlipbookComponent->GetFlipbook();

        float currentTime = GetWorld()->GetTimeSeconds();
        float ElapsedTime = currentTime - StartTimeForTimeHandle;
        UPaperSprite* paperSprite = paperFlipbook->GetSpriteAtTime(ElapsedTime);
        if (ensure(paperSprite))
        {
            if (paperSprite->HasAnySockets())
            {
                FPaperSpriteSocket* paperSpriteSocket = paperSprite->FindSocket(PaperSpriteSocketName);
                OnFireProjectile.Broadcast(paperSpriteSocket->LocalTransform);
                CheckPaperSocketTimerHandle.Invalidate();
            }
        }
    }
}

void UBNAbilityTaskFireAnimation::BroadCastComplete()
{
    if (ShouldBroadcastAbilityTaskDelegates())
    {
        OnCompleted.Broadcast(FTransform());
    }

    EndTask();
}

ABNEntityPawn* UBNAbilityTaskFireAnimation::GetEntityPawn()
{
    const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
    ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(ActorInfo->AvatarActor);
    return EntityPawn;
}
