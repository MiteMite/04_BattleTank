// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController begin play! %s"), *ControlledTank->GetName());
	}
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("cant find player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("player is %s"), *PlayerTank->GetName());
	}
	
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}