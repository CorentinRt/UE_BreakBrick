// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraWorldSubsystem.h"

#include "BreakBrick.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
	
}

void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void UCameraWorldSubsystem::Init()
{
	if (bHasBeenInit)
		return;
	
	InitMainCamera();
}

void UCameraWorldSubsystem::InitMainCamera()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MainCameraTag, FoundActors);

	if (!FoundActors.IsEmpty())
	{
		for (AActor* FoundActor : FoundActors)
		{
			if (FoundActor == nullptr)
				continue;

			Camera = Cast<ACameraActor>(FoundActor);

			if (Camera != nullptr)
				break;
		}
	}
	
	if (!IsValid(Camera))
	{
		UE_LOGFMT(LogBreakBrick, Error, "Error : No Main Camera Found in the Level ! Camera subsystem won't work !");
	}
}
