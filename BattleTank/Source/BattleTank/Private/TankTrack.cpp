// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
	auto Name = GetName();
	auto Time = GetWorld()->GetTimeSeconds();
	// UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);
	
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	// Finds the root component which is the body of the tank and cast it to a UPrimitiveComponent to allow us to add a force
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	// UE_LOG(LogTemp, Warning, TEXT("Force Applied: %s"), *ForceApplied.ToString());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}