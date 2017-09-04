// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto controlledTank = GetPawn();

	if (ensure(playerPawn) && ensure(controlledTank))
	{
		auto aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
		if (ensure(aimingComponent))
		{
			//Move towards player
			MoveToActor(playerPawn, acceptanceRadius);

			//Aim towards player
			aimingComponent->AimAt(playerPawn->GetActorLocation());
			if (aimingComponent->GetFiringState() == EFiringState::locked)
			{
				aimingComponent->Fire();
			}
			
		}
	}
}
