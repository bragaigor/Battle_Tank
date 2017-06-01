// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "Tank.h"

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void AimAt(FVector Hitlocation);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
	
private:

	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Start the tank moving the barrel so that a shot would hit where
	// the croohair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector &HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f; // 10 km
};
