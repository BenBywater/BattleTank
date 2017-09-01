// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	lastFireTime = GetWorld()->GetTimeSeconds();

}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((GetWorld()->GetTimeSeconds() - lastFireTime) < reloadTimeInSeconds)
	{
		firingState = EFiringState::reloading;
	}
	else if (IsBarrelMoving())
	{
		firingState = EFiringState::aiming;
	}
	else
	{
		firingState = EFiringState::locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet)
{
	barrel = barrelToSet;
	turret = turretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	bool movingFlag = false;
	if (ensure(barrel))
	{
		auto barrelForward = barrel->GetForwardVector();
		movingFlag = !barrelForward.Equals(aimDirection, 0.01);
	}

	return movingFlag;
}


void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (ensure(barrel))
	{
		FVector outlaunchVelocity;
		FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
		bool aimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outlaunchVelocity, startLocation,
			hitLocation, firingSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (aimSolution)
		{
			//auto barrelLocation = barrel->GetComponentLocation().ToString();
			aimDirection = outlaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(aimDirection);
		}
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDir)
{
	if (ensure(barrel) && ensure(turret))
	{
		// work=put difference between current barrel rotation and aimDirection
		auto barrelRotator = barrel->GetForwardVector().Rotation();
		auto aimAsRotator = aimDir.Rotation();
		auto deltaRotator = aimAsRotator - barrelRotator;

		barrel->Elevate(deltaRotator.Pitch);

		auto turretRotator = turret->GetForwardVector().Rotation();
		deltaRotator = aimAsRotator - turretRotator;
		turret->Rotate(deltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	
	if (firingState != EFiringState::reloading)
	{
		if (ensure(barrel))
		{
			if (ensure(projecttileBluePrint))
			{
				//spawn a projectile at barrel socket
				auto projectile = GetWorld()->SpawnActor<AProjectile>(projecttileBluePrint,
					barrel->GetSocketLocation(FName("Projectile")),
					barrel->GetSocketRotation(FName("Projectile")));
				projectile->LaunchProjectile(firingSpeed);

				lastFireTime = GetWorld()->GetTimeSeconds();

			}
		}
	}
	
}
