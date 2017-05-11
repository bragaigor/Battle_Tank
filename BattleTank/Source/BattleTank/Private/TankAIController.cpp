// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerController();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possessing %s"), *ControlledTank->GetName());
	}

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot see a Playertank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController found %s"), *PlayerTank->GetName());
	}

	
	// UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO Move towards the player

	AimTowardsPlayer();

	// TODO Fire if ready

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::AimTowardsPlayer()
{
	if (!GetControlledTank()) { return; }
	if (!GetPlayerController()) { return;  }

	GetControlledTank()->AimAt(GetPlayerController()->GetActorLocation());
	
}

ATank* ATankAIController::GetPlayerController() const
{
	// Finds the first player. The player that the user posseses
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot see a Playertank"));
		return nullptr;
	}
	return Cast<ATank>(PlayerTank);

}