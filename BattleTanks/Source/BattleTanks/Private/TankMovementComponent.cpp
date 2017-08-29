// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	if (leftTrackToSet != NULL && rightTrackToSet != NULL)
	{
		leftTrack = leftTrackToSet;
		rightTrack = rightTrackToSet;
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

	// no need to call super as we're replacing the functionality
	auto tankName = GetOwner()->GetName();
	auto moveVelocityString = MoveVelocity.ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *tankName, *moveVelocityString);
}

void UTankMovementComponent::IntendMoveForward(float move)
{
	if (leftTrack != NULL && rightTrack != NULL)
	{
		leftTrack->SetThrottle(move);
		rightTrack->SetThrottle(move);
	}
	
}


void UTankMovementComponent::IntendTurnRight(float move)
{
	leftTrack->SetThrottle(move);
	rightTrack->SetThrottle(-move);
}

