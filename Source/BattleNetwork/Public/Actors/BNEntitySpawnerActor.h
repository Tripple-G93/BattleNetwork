// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "GameplayTagContainer.h"

#include "BNEntitySpawnerActor.generated.h"

class ABNEntityPawn;
class UDataTable;

UCLASS()
class BATTLENETWORK_API ABNEntitySpawnerActor : public AActor
{
	GENERATED_BODY()
	
protected:

    UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> SpawnableEntityDataTable;

    TArray<ABNEntityPawn*> Entities;

public:	
	// Sets default values for this actor's properties
	ABNEntitySpawnerActor();

    ABNEntityPawn* SpawnEntity(FGameplayTag EntityTag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
