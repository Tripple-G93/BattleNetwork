// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BNProjectile.generated.h"

UCLASS()
class BATTLENETWORK_API ABNProjectile : public AActor
{
private:
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABNProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetActorHiddenInGame(bool bNewHidden) override;

};
