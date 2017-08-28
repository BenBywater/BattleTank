// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetBarrelReference(UTankBarrel* barrelToSet);
	void SetTurretReference(UTankTurret* turretToSet);

	void AimAt(FVector worldSpaceAim, float launchSpeed);

	UTankBarrel* barrel = NULL;
	UTankTurret* turret = NULL;

	void MoveBarrelTowards(FVector aimDirection);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

};
