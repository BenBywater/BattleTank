// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelToSet)
{
	barrel = barrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretToSet)
{
	turret = turretToSet;
}
// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (barrel)
	{
		FVector outlaunchVelocity;
		FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
		bool aimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outlaunchVelocity, startLocation,
			hitLocation, launchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (aimSolution)
		{
			//FString playerTankName = GetOwner()->GetName();
			//auto barrelLocation = barrel->GetComponentLocation().ToString();
			FVector aimDirection = outlaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(aimDirection);
			//UE_LOG(LogTemp, Warning, TEXT("Aiming at: %s"), *aimDirection.ToString());
		}
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	// work=put difference between current barrel rotation and aimDirection
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;
	
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *deltaRotator.ToString());

	barrel->Elevate(deltaRotator.Pitch);
	
	auto turretRotator = turret->GetForwardVector().Rotation();
	deltaRotator = aimAsRotator - turretRotator;
	turret->Rotate(deltaRotator.Yaw);
}
