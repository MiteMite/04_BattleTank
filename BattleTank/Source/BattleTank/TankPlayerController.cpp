// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing tank"));
	}
	UE_LOG(LogTemp, Warning, TEXT("Player controller begin play! %s"), *ControlledTank->GetName());
}

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

	FVector HitLocation; //out parameter
	//get world location if linetrace through crosshair
	if (GetSightRayHitLocation(HitLocation)) //has side effect is going to line trace
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
	}
	
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	//find the crosshaire position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewportSizeY*CrossHairYLocation);
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString());
		if (GetLookVectorHitLocation(HitLocation, LookDirection))
		{

		}

	}

	
	//HitLocation = FVector(1.0); //out parameter
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation, WorldDirection;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation+(LookDirection*LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector().ZeroVector;
		return false;
	}
}