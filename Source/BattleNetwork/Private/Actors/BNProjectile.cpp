// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNProjectile.h"

#include "Actors/BNGridActor.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameModes/BNGameModeBase.h"
#include "PaperFlipbookComponent.h"
#include "Pawns/BNEntityPawn.h"

// Sets default values
ABNProjectile::ABNProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	PaperFlipbookComponent = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, TEXT("PaperFlipbookComponent"));
	PaperFlipbookComponent->SetupAttachment(SceneComponent);

	CollisionCapsuleComponent = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CapsuleComponent"));
	CollisionCapsuleComponent->SetupAttachment(PaperFlipbookComponent);
	
	ProjectileMovementComponent = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovementComponent"));

	NextAvailableProjectile = nullptr;

	TeamFiredGameplayTag = FGameplayTag::RequestGameplayTag("Team1");
}

// Called when the game starts or when spawned
void ABNProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
	
	CollisionCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this,&ABNProjectile::OverlapBegin);
}

void ABNProjectile::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Projectile exist on the server and is replicated to clients
	if(GetLocalRole() == ROLE_Authority)
	{
		ABNEntityPawn* EntityPawn = Cast<ABNEntityPawn>(OtherActor);
		if(EntityPawn)
		{
			if(EntityPawn->GetTeamTag() != TeamFiredGameplayTag)
			{
				EntityPawn->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data);
				SetActorHiddenInGame(true);
				ResetProjectileLocation();
				if(OnProjectileDeactivateDelegate.IsBound())
				{
					OnProjectileDeactivateDelegate.Execute(this);
				}
			}
		}
	}
}

void ABNProjectile::ResetProjectileLocation()
{
	ProjectileMovementComponent->Velocity = FVector(-200, 0, 0);
}

// Called every frame
void ABNProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(GetLocalRole() == ROLE_Authority && CanWeTurnOffProjectile())
	{
		SetActorHiddenInGame(true);
		ResetProjectileLocation();
		OnProjectileDeactivateDelegate.Execute(this);
	}
}

bool ABNProjectile::CanWeTurnOffProjectile() const
{
	bool bTurnOffProjectile = false;
	ABNGameModeBase* GameModeBase = Cast<ABNGameModeBase>(GetWorld()->GetAuthGameMode());
	if(TeamFiredGameplayTag == FGameplayTag::RequestGameplayTag("Team1"))
	{
		bTurnOffProjectile = GameModeBase->GetGridActor()->GetRightMostPanelXLocation() < GetActorLocation().X;
	}
	else
	{
		bTurnOffProjectile = GameModeBase->GetGridActor()->GetLeftMostPanelXLocation() > GetActorLocation().X;
	}

	return bTurnOffProjectile;
}


void ABNProjectile::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);
	SetActorTickEnabled(!bNewHidden);

	if(bNewHidden == true)
	{
		ResetProjectileLocation();
		CollisionCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		CollisionCapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void ABNProjectile::SetProjectilesVelocity(FGameplayTag GameplayTag)
{
	TeamFiredGameplayTag = GameplayTag;
	
	if(TeamFiredGameplayTag == FGameplayTag::RequestGameplayTag("Team1"))
	{
		ProjectileMovementComponent->Velocity = ProjectileVelocity;
	}
	else
	{
		ProjectileMovementComponent->Velocity.X = -ProjectileVelocity.X;
		ProjectileMovementComponent->Velocity.Y = ProjectileVelocity.Y;
		ProjectileMovementComponent->Velocity.Z = ProjectileVelocity.Z;
	}
}

void ABNProjectile::SetTeamFiredTag(FGameplayTag NewTeamFiredGameplayTag)
{
	TeamFiredGameplayTag = NewTeamFiredGameplayTag;
}

void ABNProjectile::SetGameplayEffectSpecHandle(FGameplayEffectSpecHandle NewGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandle = NewGameplayEffectSpecHandle;
}

ABNProjectile* ABNProjectile::GetNextNextAvailableProjectile() const
{
	return NextAvailableProjectile;
}

void ABNProjectile::SetNextAvailableProjectile(ABNProjectile* Projectile)
{
	NextAvailableProjectile = Projectile;
}

