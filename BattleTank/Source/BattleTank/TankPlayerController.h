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
	//start the tank moving the barrel
	void AimTowardsCrosshair();

	//return on OUT parmaeter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
