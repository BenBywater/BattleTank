// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	ATank* GetControlledTank();
	
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitrLocation) const;

private:
	UPROPERTY(EditAnywhere)
	float crossHairX = 0.5;
	UPROPERTY(EditAnywhere)
	float crossHairY = 0.33333;
	// 10km
	UPROPERTY(EditAnywhere)
	int lineTraceRange = 1000000;

};
