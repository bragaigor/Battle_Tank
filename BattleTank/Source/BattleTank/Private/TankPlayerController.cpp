// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing %s"), *ControlledTank->GetName());
	}
	// UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out parameter
	GetSightRayHitLocation(HitLocation);
	UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	// Get World location of linetrace through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	HitLocation = FVector(12.0f, 5.f, 50.5f);
	return false;
}
