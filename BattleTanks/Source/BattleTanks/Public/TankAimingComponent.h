// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	reloading,
	aiming,
	locked
};

/**
* Responsible for helping the player aim
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* barrelToSet, UTankTurret* turretToSet);

	void AimAt(FVector hitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState firingState = EFiringState::aiming;



private: 
	// Sets default values for this component's properties
	UTankAimingComponent();

	UTankBarrel* barrel = NULL;
	UTankTurret* turret = NULL;

	void MoveBarrelTowards(FVector aimDirection);

	//1000 meters a second
	UPROPERTY(EditAnywhere, Category = "Firing")
	float firingSpeed = 4000;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float reloadTimeInSeconds = 3;
	double lastFireTime = 0;

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> projecttileBluePrint;
};
