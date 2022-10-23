// Fill out your copyright notice in the Description page of Project Settings.


#include "Structs/BNStructs.h"

bool FBNGridLocation::operator!=(const FBNGridLocation& FbnGridLocation) const
{
	return XIndex != FbnGridLocation.XIndex || YIndex != FbnGridLocation.YIndex;
}
