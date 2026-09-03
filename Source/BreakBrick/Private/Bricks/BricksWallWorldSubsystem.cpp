// Fill out your copyright notice in the Description page of Project Settings.


#include "Bricks/BricksWallWorldSubsystem.h"

#include "BreakBrick.h"
#include "Bricks/BricksWallStart.h"
#include "Bricks/BricksWall_Datas.h"
#include "Bricks/BricksWall_Settings.h"
#include "Bricks/Brick_Base.h"
#include "Kismet/GameplayStatics.h"

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
	
	GetBrickWallStartActor();
	
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
			BindBrickListeners(Brick);
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
	
	FVector BrickWallOrigin = GetBrickWallStartLocation();
	
	float GapX = InX * Datas->XSpaceBetween;
	float GapY = InY * Datas->YSpaceBetween;
	
	switch (BrickIDToCreate)
	{
	case EBrickID::SIMPLE:
		Brick = GetWorld()->SpawnActor<ABrick_Base>(*BrickClass, FVector(BrickWallOrigin.X, GapX + BrickWallOrigin.Y, -GapY + BrickWallOrigin.Z), FRotator::ZeroRotator);
		break;
	default:
		break;
	}
	
	
	return Brick;
}

void UBricksWallWorldSubsystem::ReceiveBrickDestruct(ABrick_Base* InBrick)
{
	UnbindBrickListeners(InBrick);
	
	OnOneBrickDestruct.Broadcast(InBrick);
}

void UBricksWallWorldSubsystem::ReceiveBrickBounced(ABrick_Base* InBrick)
{
	OnOneBrickBounced.Broadcast(InBrick);
}

void UBricksWallWorldSubsystem::BindBrickListeners(ABrick_Base* InBrick)
{
	InBrick->OnBrickDestruct.AddDynamic(this, &UBricksWallWorldSubsystem::ReceiveBrickDestruct);
	InBrick->OnBrickBounced.AddDynamic(this, &UBricksWallWorldSubsystem::ReceiveBrickBounced);
}

void UBricksWallWorldSubsystem::UnbindBrickListeners(ABrick_Base* InBrick)
{
	InBrick->OnBrickDestruct.RemoveDynamic(this, &UBricksWallWorldSubsystem::ReceiveBrickDestruct);
	InBrick->OnBrickBounced.RemoveDynamic(this, &UBricksWallWorldSubsystem::ReceiveBrickBounced);
}

void UBricksWallWorldSubsystem::ClearBricksWall()
{
	for (int i = 0; i < AllBricks.Num(); ++i)
	{
		ABrick_Base* Brick = AllBricks[i];
		
		if (!IsValid(Brick))
			continue;
		
		UnbindBrickListeners(Brick);
		
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

void UBricksWallWorldSubsystem::GetBrickWallStartActor()
{
	if (!GetWorld())
		return;
	
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), BrickWallStartTag, FoundActors);
	
	if (!FoundActors.IsEmpty())
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor == nullptr)
				continue;

			BrickWallStart = Cast<ABricksWallStart>(FoundActor);

			if (BrickWallStart != nullptr)
				break;
		}
	}
	
	if (!IsValid(BrickWallStart))
	{
		UE_LOGFMT(LogBreakBrick, Error, "Error : No BrickWallStart  Found in the Level ! Brick Wall won't generate at right location !");
	}
}

FVector UBricksWallWorldSubsystem::GetBrickWallStartLocation() const
{
	if (!IsValid(BrickWallStart))
		return FVector::ZeroVector;
		
	return BrickWallStart->GetActorLocation();
}
