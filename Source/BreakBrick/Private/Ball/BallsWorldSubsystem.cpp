// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball/BallsWorldSubsystem.h"

#include "Ball/BallSpawnPoint.h"
#include "Ball/Ball_BB.h"
#include "Bricks/BricksWall_Datas.h"
#include "Bricks/BricksWall_Settings.h"
#include "Kismet/GameplayStatics.h"

void UBallsWorldSubsystem::Init()
{
	LoadBricksWallDatasFromConfig();
	
	FindBallsSpawnPoint();
	
	ClearBalls();
	
	FindExistingBalls();
}

void UBallsWorldSubsystem::ClearBalls()
{
	for (int i = 0; i < AllBalls.Num(); ++i)
	{
		ABall_BB* Ball = AllBalls[i];
		
		if (!IsValid(Ball))
			continue;
		
		UnbindBallListeners(Ball);
		
		Ball->Destroy();
	}
	
	AllBalls.Empty();
}

void UBallsWorldSubsystem::LoadBricksWallDatasFromConfig()
{
	const UBricksWall_Settings* BricksWall_Settings = GetDefault<UBricksWall_Settings>();
	
	if (!IsValid(BricksWall_Settings))
		return;
	
	Datas = BricksWall_Settings->BricksWall_Datas.LoadSynchronous();
}


void UBallsWorldSubsystem::FindExistingBalls()
{
	if (!GetWorld())
		return;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), BallTag, FoundActors);
	
	if (!FoundActors.IsEmpty())
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor == nullptr)
				continue;

			ABall_BB* Ball = Cast<ABall_BB>(FoundActor);

			if (Ball == nullptr)
				break;
			
			AllBalls.Add(Ball);
			BindBallListeners(Ball);
		}
	}
}

void UBallsWorldSubsystem::FindBallsSpawnPoint()
{
	if (!GetWorld())
		return;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), BallSpawnPointTag, FoundActors);
	
	if (!FoundActors.IsEmpty())
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor == nullptr)
				continue;

			 BallSpawnPoint = Cast<ABallSpawnPoint>(FoundActor);

			if (BallSpawnPoint != nullptr)
				return;
		}
	}
}

ABall_BB* UBallsWorldSubsystem::CreateNewBall(bool InDirectlyInitBall)
{
	if (!IsValid(BallSpawnPoint) || !IsValid(GetWorld()))
		return nullptr;
	
	if (!IsValid(Datas))
		return nullptr;
	
	if (Datas->BallSubclass == nullptr)
		return nullptr;
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	ABall_BB* Ball = GetWorld()->SpawnActor<ABall_BB>(Datas->BallSubclass, BallSpawnPoint->GetActorLocation(), BallSpawnPoint->GetActorRotation());
	
	if (!IsValid(Ball))
		return nullptr;
	
	AllBalls.Add(Ball);
	BindBallListeners(Ball);
	
	if (InDirectlyInitBall)
	{
		Ball->Init();
	}
	
	return Ball;
}

void UBallsWorldSubsystem::ReceiveBallDestruct(ABall_BB* InBall)
{
	if (!IsValid(InBall))
		return;
	
	UnbindBallListeners(InBall);
	
	AllBalls.Remove(InBall);
	
	OnOneBallDestruct.Broadcast(InBall);
}

void UBallsWorldSubsystem::ReceiveBallBounced(ABall_BB* InBall)
{
	if (!IsValid(InBall))
		return;
	
	OnOneBallBounced.Broadcast(InBall);
}

bool UBallsWorldSubsystem::AllBricksAreDestroyed()
{
	if (AllBalls.IsEmpty())
		return true;
	
	for (int i = 0; i < AllBalls.Num(); ++i)
	{
		ABall_BB* Ball = AllBalls[i];
		
		if (!IsValid(Ball))
			continue;
		
		return false;
	}
	
	return true;
}

FVector UBallsWorldSubsystem::GetBallSpawnPointLocation() const
{
	if (!IsValid(BallSpawnPoint))
		return FVector::ZeroVector;
	
	return BallSpawnPoint->GetActorLocation();
}

void UBallsWorldSubsystem::BindBallListeners(ABall_BB* InBall)
{
	if (!IsValid(InBall))
		return;
	
	InBall->OnBallDestruct.AddDynamic(this, &UBallsWorldSubsystem::ReceiveBallDestruct);
	InBall->OnBallBounced.AddDynamic(this, &UBallsWorldSubsystem::ReceiveBallBounced);
}

void UBallsWorldSubsystem::UnbindBallListeners(ABall_BB* InBall)
{
	if (!IsValid(InBall))
		return;
	
	InBall->OnBallDestruct.RemoveDynamic(this, &UBallsWorldSubsystem::ReceiveBallDestruct);
	InBall->OnBallBounced.RemoveDynamic(this, &UBallsWorldSubsystem::ReceiveBallBounced);
}
