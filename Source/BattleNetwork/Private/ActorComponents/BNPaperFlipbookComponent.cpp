// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/BNPaperFlipbookComponent.h"

#include <PaperFlipbook.h>

UBNPaperFlipbookComponent::UBNPaperFlipbookComponent(const FObjectInitializer& ObjectInitializer) 
    : Super(ObjectInitializer)
{
    ShouldCheckForSocket = false;
}

void UBNPaperFlipbookComponent::SocketToLookFor(FName NewPaperSpriteSocketName)
{
    PaperSpriteSocketName = NewPaperSpriteSocketName;

    ShouldCheckForSocket = true;
}

void UBNPaperFlipbookComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (ShouldCheckForSocket)
    {
        FindSocket();
    }
}

void UBNPaperFlipbookComponent::FindSocket()
{
    int CurrentFlipBookFrame = GetPlaybackPositionInFrames();
    FTransform SocketTransformLocation;
    if (GetFlipbook()->FindSocket(PaperSpriteSocketName, CurrentFlipBookFrame, SocketTransformLocation))
    {
        SocketTransformLocation *= GetComponentTransform();

        OnFoundSocket.Broadcast(SocketTransformLocation);

        ShouldCheckForSocket = false;
    }
}
