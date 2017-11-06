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

EFiringState UTankAimingComponent::GetFiringState() const
{
	return firingState;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return ammoCount;
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// calculate UI firing state
	if (ammoCount <= 0)
	{
		firingState = EFiringState::outOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - lastFireTime) < reloadTimeInSeconds)
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
	// calculates if barrel is moving for player UI
	bool movingFlag = false;
	if (barrel != NULL)
	{
		auto barrelForward = barrel->GetForwardVector();
		movingFlag = !barrelForward.Equals(aimDirection, 0.01);
	}

	return movingFlag;
}


void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (barrel != NULL)
	{
		FVector outlaunchVelocity;
		FVector startLocation = barrel->GetSocketLocation(FName("Projectile"));
		// Returns the launch velocity needed for a projectile, returns cool if projectile can hit en location
		bool aimSolution = UGameplayStatics::SuggestProjectileVelocity(this, outlaunchVelocity, startLocation,
			hitLocation, firingSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (aimSolution)
		{
			// move barrel
			aimDirection = outlaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(aimDirection);
		}
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDir)
{
	if (barrel != NULL && turret != NULL)
	{
		// work=put difference between current barrel rotation and aimDirection
		auto barrelRotator = barrel->GetForwardVector().Rotation();
		auto aimAsRotator = aimDir.Rotation();
		auto deltaRotator = aimAsRotator - barrelRotator;

		barrel->Elevate(deltaRotator.Pitch);
		// always yaw the shortest way
		if (FMath::Abs(deltaRotator.Yaw) < 180)
		{
			turret->Rotate(deltaRotator.Yaw);
		}
		else
		{
			turret->Rotate(-deltaRotator.Yaw);
		}
	}
	
}

void UTankAimingComponent::Fire()
{
	
	if (firingState == EFiringState::locked || firingState == EFiringState::aiming)
	{
		if (barrel != NULL)
		{
			if (projecttileBluePrint != NULL)
			{
				//spawn a projectile at barrel socket
				auto projectile = GetWorld()->SpawnActor<AProjectile>(projecttileBluePrint,
					barrel->GetSocketLocation(FName("Projectile")),
					barrel->GetSocketRotation(FName("Projectile")));
				projectile->LaunchProjectile(firingSpeed);

				lastFireTime = GetWorld()->GetTimeSeconds();
				ammoCount--;
			}
		}
	}
	
}

