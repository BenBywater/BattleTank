// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float acceptanceRadius = 100;

private:

	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	virtual void SetPawn(APawn* inPawn) override;
	
	UFUNCTION()
	void OnPossessedTankDeath();
	
};
