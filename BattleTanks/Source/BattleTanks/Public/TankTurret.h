// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downard speed, and +1 is max up movement
	void Rotate(float relativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float maxDegreesPerSecond = 45;
	
};
