// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float move);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float move);

private:
	// called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	UTankTrack *leftTrack = NULL;
	UTankTrack *rightTrack = NULL;
	
};
