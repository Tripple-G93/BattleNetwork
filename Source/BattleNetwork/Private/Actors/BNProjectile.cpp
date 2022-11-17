// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BNProjectile.h"

// Sets default values
ABNProjectile::ABNProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABNProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABNProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

