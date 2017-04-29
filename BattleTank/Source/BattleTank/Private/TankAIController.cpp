// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
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

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
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