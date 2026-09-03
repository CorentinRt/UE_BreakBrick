// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BricksWallStart.generated.h"

UCLASS()
class BREAKBRICK_API ABricksWallStart : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABricksWallStart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
