// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void LaunchProjectile(float speed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float destroyDelay = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float projectileDamage = 20.f;

	UProjectileMovementComponent* projectileMovement = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* collisionMesh = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* launchBlast = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* impactBlast = NULL;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* explosionForce = NULL;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit);

	void OnTimerExpire();

};
