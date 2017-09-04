// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	auto deltaTime = GetWorld()->GetDeltaSeconds();
	auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// required acceleration this frame to correct
	auto correctionAcceleration = (-slippageSpeed / deltaTime) * GetRightVector();

	// calculate and apply sideways (f = m a)
	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) - 2;
	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	currentThrottle = FMath::Clamp<float>(currentThrottle + throttle, -1, 1);
}

void UTankTrack::OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit)
{
	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}

void UTankTrack::DriveTrack()
{
	FVector forceApplied = GetForwardVector() * (currentThrottle * trackMaxDrivingForce);
	FVector forceLocation = GetComponentLocation();

	UPrimitiveComponent *tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}