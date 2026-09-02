// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_BB.generated.h"

class UBricksWallWorldSubsystem;
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
	
	
protected:
	UFUNCTION()
	void InitCameraWorldSubsystem();
	
	UFUNCTION()
	void InitBricksWallSubsystem();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitSubsystems();
	
private:
	
	UPROPERTY()
	UBricksWallWorldSubsystem* BricksWallWorldSubsystem;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void StartGame();
};
