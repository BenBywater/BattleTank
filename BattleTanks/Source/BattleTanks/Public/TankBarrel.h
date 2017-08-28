// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downard speed, and +1 is max up movement
	void Elevate(float relativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees = 0;

	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees = 40;
};
