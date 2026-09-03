// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameMode_BB.h"

#include "Ball/BallsWorldSubsystem.h"
#include "Bricks/BricksWallWorldSubsystem.h"
#include "Bricks/Brick_Base.h"
#include "Ball/Ball_BB.h"
#include "Camera/CameraWorldSubsystem.h"
#include "Score/ScoreWorldSubsystem.h"

void AGameMode_BB::BeginPlay()
{
	Super::BeginPlay();
	
	InitSubsystems();
}

void AGameMode_BB::InitSubsystems()
{
	InitCameraWorldSubsystem();
	
	InitBallsSubsystem();
	
	InitBricksWallSubsystem();
	
	InitScoreSubsystem();
	
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
	
	BricksWallWorldSubsystem->OnOneBrickDestruct.AddDynamic(this, &AGameMode_BB::ReactOnOneBrickDestruct);
	BricksWallWorldSubsystem->OnOneBrickBounced.AddDynamic(this, &AGameMode_BB::ReactOnOneBrickBounced);
	
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

void AGameMode_BB::InitBallsSubsystem()
{
	if (!GetWorld())
		return;
	
	BallsWorldSubsystem = GetWorld()->GetSubsystem<UBallsWorldSubsystem>();
	
	if (!IsValid(BallsWorldSubsystem))
		return;
	
	BallsWorldSubsystem->OnOneBallDestruct.AddDynamic(this, &AGameMode_BB::ReactOnOneBallDestruct);
	
	BallsWorldSubsystem->Init();
}

void AGameMode_BB::ReactOnOneBrickDestruct(ABrick_Base* InBrick)
{
	if (!IsValid(InBrick))
		return;
	
	if (!IsValid(ScoreWorldSubsystem))
		return;
	
	ScoreWorldSubsystem->AddScore(InBrick->GetScoreOnDestruct());
}

void AGameMode_BB::ReactOnOneBrickBounced(ABrick_Base* InBrick)
{
	if (!IsValid(InBrick))
    		return;
    	
    if (!IsValid(ScoreWorldSubsystem))
    	return;
	
    ScoreWorldSubsystem->AddScore(InBrick->GetScoreOnBounced());
	
	if (!IsValid(BricksWallWorldSubsystem))
		return;
	
	if (BricksWallWorldSubsystem->AllBricksAreDestroyed())
	{
		ReceiveGameFinished(EGameFinishedID::ALL_BRICKS_DESTROYED);
	}
	else
	{
		
	}
}

void AGameMode_BB::ReactOnOneBallDestruct(ABall_BB* InBall)
{
	if (!IsValid(BallsWorldSubsystem))
		return;
	
	if (BallsWorldSubsystem->AllBricksAreDestroyed())
	{
		ReceiveGameFinished(EGameFinishedID::ALL_BALLS_DESTROYED);
	}
	else
	{
		
	}
}

ABall_BB* AGameMode_BB::StartGame(bool InSpawnFirstBall, bool InDirectlyInitFirstBall)
{
	if (!IsValid(BricksWallWorldSubsystem))
		return nullptr;
	
	BricksWallWorldSubsystem->GenerateNewBricksWall();
	
	ABall_BB* CreatedBall = nullptr;
	
	if (InSpawnFirstBall)
	{
		if (!IsValid(BallsWorldSubsystem))
			return nullptr;
		
		CreatedBall = BallsWorldSubsystem->CreateNewBall(InDirectlyInitFirstBall);
	}
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		5.f,
		FColor::Orange,
		"Start Game !"
		);
	
	return CreatedBall;
}
