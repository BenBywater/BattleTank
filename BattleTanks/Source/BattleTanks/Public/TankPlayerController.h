// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& hitLocation) const;

	bool GetLookVectorHitLocation(FVector lookDirection, FVector& hitrLocation) const;

	
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* aimCompRef);
private:
	
	UPROPERTY(EditAnywhere)
	float crossHairX = 0.5;

	UPROPERTY(EditAnywhere)
	float crossHairY = 0.33333;

	// 10km
	UPROPERTY(EditAnywhere)
	int32 lineTraceRange = 1000000;

};
