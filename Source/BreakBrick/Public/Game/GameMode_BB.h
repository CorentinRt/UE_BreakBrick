// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_BB.generated.h"

class ABrick_Base;
class ABall_BB;
class UBricksWallWorldSubsystem;
class UScoreWorldSubsystem;

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
	
	UFUNCTION()
	void InitScoreSubsystem();
	
	UFUNCTION()
	void InitMainBall();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitSubsystems();
	
	UFUNCTION()
	void GetMainBall();
	
private:
	
	UPROPERTY()
	TObjectPtr<UBricksWallWorldSubsystem> BricksWallWorldSubsystem;
	
	UPROPERTY()
	TObjectPtr<UScoreWorldSubsystem> ScoreWorldSubsystem;
	
	
	UPROPERTY()
	FName MainBallTag = "MainBall";
	
	
	UFUNCTION()
	void ReactOnOneBrickDestruct(ABrick_Base* InBrick);
	
	UFUNCTION()
	void ReactOnOneBrickBounced(ABrick_Base* InBrick);
	
public:
	
	UFUNCTION(BlueprintCallable)
	void StartGame();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TObjectPtr<ABall_BB> MainBall;
};
