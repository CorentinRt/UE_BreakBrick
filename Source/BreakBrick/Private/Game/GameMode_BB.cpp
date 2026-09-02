// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameMode_BB.h"

#include "Bricks/BricksWallWorldSubsystem.h"
#include "Camera/CameraWorldSubsystem.h"

void AGameMode_BB::BeginPlay()
{
	Super::BeginPlay();
	
	InitSubsystems();
}

void AGameMode_BB::InitSubsystems()
{
	InitCameraWorldSubsystem();
	
	InitBricksWallSubsystem();
	
	ReceiveInitSubsystems();
}

void AGameMode_BB::InitCameraWorldSubsystem()
{
	if (!GetWorld())
		return;
	
	UCameraWorldSubsystem* CameraWorldSubsystem = GetWorld()->GetSubsystem<UCameraWorldSubsystem>();
	
	if (!CameraWorldSubsystem)
		return;
	
	CameraWorldSubsystem->Init();
}

void AGameMode_BB::InitBricksWallSubsystem()
{
	if (!GetWorld())
		return;
	
	BricksWallWorldSubsystem = GetWorld()->GetSubsystem<UBricksWallWorldSubsystem>();
	
	if (!IsValid(BricksWallWorldSubsystem))
		return;
	
	BricksWallWorldSubsystem->Init();
}

void AGameMode_BB::StartGame()
{
	if (!IsValid(BricksWallWorldSubsystem))
		return;
	
	BricksWallWorldSubsystem->GenerateNewBricksWall();
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Orange,
		"Start Game !"
		);
}
