// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	// UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward throw: %f"), Throw);
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO prevent double speed due to dual control use. Unbind one of the movements in blueprint
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal(); // Comes from the path finder 

	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention); // Uses cosine function
	IntendMoveForward(ForwardThrow);

	auto AIRotationThrow = FVector::CrossProduct(TankForward, AIForwardIntention);// Uses Sine function
	IntendTurnRight(AIRotationThrow.Z);

	// UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *VelocityString);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	// UE_LOG(LogTemp, Warning, TEXT("Intend Move Forward throw: %f"), Throw);
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	// TODO prevent double speed due to dual control use 
}