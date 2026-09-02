// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/BricksWallWorldSubsystem.h"

#include "Bricks/BricksWall_Datas.h"
#include "Bricks/BricksWall_Settings.h"
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
	
	LoadBricksWallDatasFromConfig();
	
	ClearBricksWall();
}

void UBricksWallWorldSubsystem::LoadBricksWallDatasFromConfig()
{
	const UBricksWall_Settings* BricksWall_Settings = GetDefault<UBricksWall_Settings>();
	
	if (!IsValid(BricksWall_Settings))
		return;
	
	Datas = BricksWall_Settings->BricksWall_Datas.LoadSynchronous();
}

void UBricksWallWorldSubsystem::GenerateNewBricksWall()
{
	if (!IsValid(Datas))
		return;
	
	if (!AllBricks.IsEmpty())
	{
		ClearBricksWall();
	}
	
	int TempXSize = Datas->TotalX;
	int TempYSize = Datas->TotalY;
	
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
	if (Datas->BricksIdToSubClasses.IsEmpty())
		return nullptr;
	
	EBrickID BrickIDToCreate = EBrickID::SIMPLE;
	
	ABrick_Base* Brick = nullptr;
	
	const TSubclassOf<ABrick_Base>* BrickClass = Datas->BricksIdToSubClasses.Find(BrickIDToCreate);
	
	if (!BrickClass || !*BrickClass)
	{
		return nullptr;
	}
	
	float GapX = InX * Datas->XSpaceBetween;
	float GapY = -InY * Datas->YSpaceBetween;
	
	switch (BrickIDToCreate)
	{
	case EBrickID::SIMPLE:
		Brick = GetWorld()->SpawnActor<ABrick_Base>(*BrickClass, FVector(0.f, GapX, GapY), FRotator::ZeroRotator);
		break;
	default:
		break;
	}
	
	
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
