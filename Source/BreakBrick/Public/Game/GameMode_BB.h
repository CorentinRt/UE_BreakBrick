// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_BB.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API AGameMode_BB : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION()
	virtual void BeginPlay() override;
	
	
	UFUNCTION()
	void InitSubsystems();
	
	UFUNCTION()
	void InitCameraWorldSubsystem();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitSubsystems();
};
