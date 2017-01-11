// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATank* GetControlledTank() const;
	void BeginPlay() override;
	void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere,Category="TankPlayerController")
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere, Category = "TankPlayerController")
	float CrossHairYLocation = 0.333f;
	UPROPERTY(EditAnywhere, Category = "TankPlayerController")
	float LineTraceRange = 1000000;
	//start the tank moving the barrel
	void AimTowardsCrosshair();

	//return on OUT parmaeter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const;
};
