// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (aimingComponent != NULL)
	{

		FoundAimingComponent(aimingComponent);
	}
}

void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetPawn() != NULL)
	{
		auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (aimingComponent != NULL)
		{
			FVector hitLocation;
			if (GetSightRayHitLocation(hitLocation))
			{
				aimingComponent->AimAt(hitLocation);
			}

		}
	}
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& hitLocation) const
{
	// Find the crosshair position
	//"De-project" the screeb position of the crosshair to a world direction
	// Line-trace along that look direction, and see what we hit(up tp max range)
	int32 viewX, viewY;
	FVector worldLocation, worldDirection;
	GetViewportSize(viewX, viewY);
	float screenLocationX = viewX * crossHairX;
	float screenLocationY = viewY * crossHairY;

	FVector2D screenLocation = FVector2D(screenLocationX, screenLocationY);
	if (DeprojectScreenPositionToWorld(screenLocationX, screenLocationY, worldLocation, worldDirection))
	{
		return GetLookVectorHitLocation(worldDirection, hitLocation);
	}
	
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector& hitLocation) const
{
	bool returnFlag = false;
	FHitResult hitResult;
	auto startLocation = PlayerCameraManager->GetCameraLocation();
	auto endLocation = startLocation + (lookDirection * lineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECollisionChannel::ECC_Camera))
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

void ATankPlayerController::SetPawn(APawn* inPawn)
{
	Super::SetPawn(inPawn);
	if (inPawn)
	{
		auto possessedTank = Cast<ATank>(inPawn);
		if (possessedTank != NULL)
		{
			possessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
		}
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Players Tank just died"));
	StartSpectatingOnly();
	GetWorld()->GetTimerManager().SetTimer(RestartTimerHandle, this, &ATankPlayerController::RestartLevel, 5.f, false);
}

void ATankPlayerController::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}