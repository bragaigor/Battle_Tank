// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO should this really tick

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	// auto OurTankName = GetOwner()->GetName();
	// auto BarrelLocation = Barrel->GetComponentLocation();
	// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());

	if (!Barrel) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("TankAimingComponent.cpp: No barrel found"));
		return; 
	}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter should be presetn to prevent bug
	);

	// Calculate the OutLaunchVelocity
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();

		// UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());

		// Move the Barrel
		auto Time = GetWorld()->GetTimeSeconds();
		/// UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution found"), Time);
		MoveBarrelTowards(AimDirection);
	}
	else 
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found"), Time);
	}
	
}

// Sets the barrel through blueprint
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet) { return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) 
{
	if (!TurretToSet) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) 
{
	// Workout difference between current barrel rotaion, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch); // TODO remove magic number
	Turret->Rotate(DeltaRotator.Yaw);
}