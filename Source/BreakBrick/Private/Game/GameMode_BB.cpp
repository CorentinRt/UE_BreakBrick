// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameMode_BB.h"

#include "BreakBrick.h"
#include "Ball/Ball_BB.h"
#include "Bricks/BricksWallWorldSubsystem.h"
#include "Camera/CameraWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Score/ScoreWorldSubsystem.h"

void AGameMode_BB::BeginPlay()
{
	Super::BeginPlay();
	
	InitSubsystems();
}

void AGameMode_BB::InitSubsystems()
{
	InitCameraWorldSubsystem();
	
	InitBricksWallSubsystem();
	
	InitScoreSubsystem();
	
	InitMainBall();
	
	ReceiveInitSubsystems();
}

void AGameMode_BB::InitCameraWorldSubsystem()
{
	if (!GetWorld())
		return;
	
	UCameraWorldSubsystem* CameraWorldSubsystem = GetWorld()->GetSubsystem<UCameraWorldSubsystem>();
	
	if (!IsValid(CameraWorldSubsystem))
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

void AGameMode_BB::InitScoreSubsystem()
{
	if (!GetWorld())
		return;
	
	ScoreWorldSubsystem = GetWorld()->GetSubsystem<UScoreWorldSubsystem>();
	
	if (!IsValid(ScoreWorldSubsystem))
		return;
	
	ScoreWorldSubsystem->Init();
}

void AGameMode_BB::InitMainBall()
{
	GetMainBall();
	
	if (!IsValid(MainBall))
		return;
	
	MainBall->Init();
}

void AGameMode_BB::GetMainBall()
{
	if (!GetWorld())
		return;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MainBallTag, FoundActors);
	
	if (!FoundActors.IsEmpty())
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor == nullptr)
				continue;

			MainBall = Cast<ABall_BB>(FoundActor);

			if (MainBall != nullptr)
				break;
		}
	}
	
	if (!IsValid(MainBall))
	{
		UE_LOGFMT(LogBreakBrick, Error, "Error : No Main Ball Found in the Level ! Ball won't launch and game won't work !");
	}
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
