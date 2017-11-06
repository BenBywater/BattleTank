// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* leftTrackToSet, UTankTrack* rightTrackToSet)
{
	// Initialise track tracks
	if (leftTrackToSet != NULL && rightTrackToSet != NULL)
	{
		leftTrack = leftTrackToSet;
		rightTrack = rightTrackToSet;
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

	// no need to call super as we're replacing the functionality

	auto tanklForward = GetOwner()->GetActorForwardVector();
	auto aiForwardIntention = MoveVelocity.GetSafeNormal();

	// Dot product, magnitude of planyer tank and AI tank multiplied by cosine
	// Allows AI tanks to calculate 90 degree alignment
	auto forwardThrow = FVector::DotProduct(tanklForward, aiForwardIntention);

	IntendMoveForward(forwardThrow);
	// vector cross product magnitude of two vectos multiplied by the sin 
	// angle of the vectors multiplied by N where N is a unit vector 
	// perpendicular to the other vectors
	auto rightThrow = FVector::CrossProduct(tanklForward, aiForwardIntention).Z;
	IntendTurnRight(rightThrow);
}

void UTankMovementComponent::IntendMoveForward(float move)
{
	// move tank forward or backward
	if (leftTrack != NULL && rightTrack != NULL)
	{
		leftTrack->SetThrottle(move);
		rightTrack->SetThrottle(move);
	}
	
}


void UTankMovementComponent::IntendTurnRight(float move)
{
	// rotate tank left or right
	if (leftTrack != NULL && rightTrack != NULL)
	{
		leftTrack->SetThrottle(move);
		rightTrack->SetThrottle(-move);
	}
}

