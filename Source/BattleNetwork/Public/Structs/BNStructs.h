// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BNStructs.generated.h"

/**
 * Struct defining a list of gameplay effects, a tag, and targeting info
 * These containers are defined statically in blueprints or assets and then turn into Specs at runtime
 */
USTRUCT(BlueprintType)
struct FBNGridLocation
{
	GENERATED_BODY()

public:
	
	FBNGridLocation() : XIndex(0), YIndex(0) {}
	FBNGridLocation(const int32 NewXIndex, const int32 NewYIndex) : XIndex(NewXIndex) , YIndex(NewYIndex) {}

	UPROPERTY()
	int32 XIndex;

	UPROPERTY()
	int32 YIndex;
};