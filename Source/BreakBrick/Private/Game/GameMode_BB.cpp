// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameMode_BB.h"

#include "Camera/CameraWorldSubsystem.h"

void AGameMode_BB::BeginPlay()
{
	Super::BeginPlay();
	
	InitSubsystems();
}

void AGameMode_BB::InitSubsystems()
{
	InitCameraWorldSubsystem();
	
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
