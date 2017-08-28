// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	auto controllerTank = Cast<ATank>(GetPawn());
	auto playerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (playerPawn)
	{
		controllerTank->AimAt(playerPawn->GetActorLocation());
		controllerTank->Fire();
	}
}
