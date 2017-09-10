// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h"

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

void ATankAIController::SetPawn(APawn* inPawn)
{
	Super::SetPawn(inPawn);
	if (inPawn)
	{
		auto possessedTank = Cast<ATank>(inPawn);
		if (ensure(possessedTank))
		{
			possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
		}
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (GetPawn() != NULL)
	{
		GetPawn()->DetachFromControllerPendingDestroy();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Tank just died"));
}