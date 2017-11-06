// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"



// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	// set current health
	currentHealth = startingHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 damageToApply = FMath::Clamp(damagePoints, 0, currentHealth);
	// apply damage
	currentHealth -= damageToApply;
	if (currentHealth <= 0)
	{
		// broadcast death of pawn
		OnDeath.Broadcast();
	}
	return damageToApply;
}

float ATank::GetHealthPercent() const
{
	// calculate health
	return (float)currentHealth / (float)startingHealth;
}
