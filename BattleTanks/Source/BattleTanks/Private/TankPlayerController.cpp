// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto controlledTank = GetControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(controlledTank->GetName()));
	}
	
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank() != NULL)
	{
		FVector hitLocation;
		if (GetSightRayHitLocation(hitLocation))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *hitLocation.ToString());
			GetControlledTank()->AimAt(hitLocation);
		}
		
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	// Find the crosshair position
	//"De-project" the screeb position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit(up tp max range)
	int viewX, viewY;
	FVector worldLocation, worldDirection;
	GetViewportSize(viewX, viewY);
	float screenLocationX = viewX * crossHairX;
	float screenLocationY = viewY * crossHairY;

	FVector2D screenLocation = FVector2D(screenLocationX, screenLocationY);
	if (DeprojectScreenPositionToWorld(screenLocationX, screenLocationY, worldLocation, worldDirection))
	{
		GetLookVectorHitLocation(worldDirection, hitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	bool returnFlag = false;
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Visibility))
	{
		hitLocation = hitResult.Location;
		returnFlag = true;
	}
	else
	{
		hitLocation = FVector(0, 0, 0);
	}
	return returnFlag;
}

ATank* ATankPlayerController::GetControlledTank() 
{
	return Cast<ATank>(GetPawn());
}


