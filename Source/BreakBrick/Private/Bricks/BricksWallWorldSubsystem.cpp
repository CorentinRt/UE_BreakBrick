// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/BricksWallWorldSubsystem.h"

#include "Bricks/Brick_Base.h"

void UBricksWallWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	
}

void UBricksWallWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

void UBricksWallWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void UBricksWallWorldSubsystem::Init()
{
	if (bHasBeenInit)
		return;
	
	ClearBricksWall();
}

void UBricksWallWorldSubsystem::GenerateNewBricksWall()
{
	if (!AllBricks.IsEmpty())
	{
		ClearBricksWall();
	}
	
	int TempXSize = 5;
	int TempYSize = 7;
	
	ABrick_Base* Brick = nullptr;
	
	for (int i = 0; i < TempXSize; ++i)
	{
		for (int j = 0; j < TempYSize; ++j)
		{
			Brick = CreateBrick(i, j);
			
			if (!IsValid(Brick))
				continue;
				
			AllBricks.Add(Brick);
			AddBrickDestructListener(Brick);
		}
	}
	
}

ABrick_Base* UBricksWallWorldSubsystem::CreateBrick(int InX, int InY)
{
	ABrick_Base* Brick = GetWorld()->SpawnActor<ABrick_Base>();
	
	return Brick;
}

void UBricksWallWorldSubsystem::ReceiveBrickDestruct(ABrick_Base* InBrick)
{
	RemoveBrickDestructListener(InBrick);
	
	OnOneBrickDestruct.Broadcast();
}

void UBricksWallWorldSubsystem::AddBrickDestructListener(ABrick_Base* InBrick)
{
	InBrick->OnBrickDestruct.AddDynamic(this, &UBricksWallWorldSubsystem::ReceiveBrickDestruct);
}

void UBricksWallWorldSubsystem::RemoveBrickDestructListener(ABrick_Base* InBrick)
{
	InBrick->OnBrickDestruct.RemoveDynamic(this, &UBricksWallWorldSubsystem::ReceiveBrickDestruct);
}

void UBricksWallWorldSubsystem::ClearBricksWall()
{
	for (int i = 0; i < AllBricks.Num(); ++i)
	{
		ABrick_Base* Brick = AllBricks[i];
		
		if (!IsValid(Brick))
			continue;
		
		RemoveBrickDestructListener(Brick);
		
		Brick->Destroy();
	}
	
	AllBricks.Empty();
}

bool UBricksWallWorldSubsystem::AllBricksAreDestroyed()
{
	if (AllBricks.IsEmpty())
		return true;
	
	for (int i = 0; i < AllBricks.Num(); ++i)
	{
		ABrick_Base* Brick = AllBricks[i];
		
		if (IsValid(Brick))
			return false;
	}
	
	return true;
}
