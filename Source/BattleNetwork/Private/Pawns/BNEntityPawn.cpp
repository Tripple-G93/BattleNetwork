// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BNEntityPawn.h"

#include "Actors/BNGridActor.h"
#include "PaperFlipbookComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

ABNEntityPawn::ABNEntityPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	PaperFlipbookComponent = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);
	PaperFlipbookComponent->bReplicatePhysicsToAutonomousProxy = false;
	PaperFlipbookComponent->SetIsReplicated(true);
}

void ABNEntityPawn::FlipEntity() const
{
	FVector LocationOffset = PaperFlipbookComponent->GetRelativeLocation();
	LocationOffset.Y *= -1;

	PaperFlipbookComponent->SetRelativeLocation(LocationOffset);
}

void ABNEntityPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABNEntityPawn, TeamTag);
	DOREPLIFETIME(ABNEntityPawn, GridActorReference);
	DOREPLIFETIME(ABNEntityPawn, XIndex);
	DOREPLIFETIME(ABNEntityPawn, YIndex);
}

/*
 * Setters
 */

void ABNEntityPawn::SetGridActorReference(ABNGridActor* GridActor)
{
	GridActorReference = GridActor;
}

void ABNEntityPawn::SetTeamTag(FGameplayTag NewTeamTag)
{
	TeamTag = NewTeamTag;
}

void ABNEntityPawn::SetNewXIndexPosition(const int32 NewXIndex)
{
	XIndex = NewXIndex;
}

void ABNEntityPawn::SetNewYIndexPosition(const int32 NewYIndex)
{
	YIndex = NewYIndex;
}

/*
 * End Setters
 */

/*
 * Getters
 */

int32 ABNEntityPawn::GetXIndexPosition() const
{
	return XIndex;
}

int32 ABNEntityPawn::GetYIndexPosition() const
{
	return YIndex;
}

FGameplayTag ABNEntityPawn::GetTeamTag() const
{
	return TeamTag;
}

/*
 * End Getters
 */

// Called when the game starts or when spawned
void ABNEntityPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABNEntityPawn::AttemptToMoveHorizontally(const float Value)
{
	// TODO BN: Implement the right 
	
	if(Value < 0)
	{
		if(MoveEntityLeftRPC_Validate())
		{
			if(IsLocallyControlled())
			{
				MoveEntityLeftRPC_Implementation();
			}

			MoveEntityLeftRPC();
		}
	}
	else if(Value > 0)
	{
		ABNGridActor* GridActor = GetOwner<ABNGridActor>();
		if(GridActor->CanEntityMoveRight(this))
		{
			//GridActor->MoveEntityToNewPanel(this);
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Move Right"));
		}
	}

}

void ABNEntityPawn::AttemptToMoveVertically(float Value)
{
	// TODO BN: Add code to be able to move the entity vertically 

}


/*
 * Server RPC
 */

void ABNEntityPawn::MoveEntityLeftRPC_Implementation()
{
	GridActorReference->MoveEntityToNewPanel(this, XIndex - 1, YIndex);
}

bool ABNEntityPawn::MoveEntityLeftRPC_Validate()
{
	return GridActorReference->CanEntityMoveLeft(this);
}


