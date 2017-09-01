// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTurret.h"



void UTankTurret::Rotate(float relativeSpeed)
{
	// GetWorld()->DeltaTimeSeconds ensures its frame depentant
	relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
	auto rotationChange = relativeSpeed * (maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds);
	auto rotation = RelativeRotation.Yaw + rotationChange;
	SetRelativeRotation(FRotator(0, rotation, 0));
}


