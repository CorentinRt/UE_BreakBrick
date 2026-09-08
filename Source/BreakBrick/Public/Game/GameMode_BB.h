// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFinished/GameFinishedID.h"
#include "RoundFinished/RoundFinishedID.h"
#include "GameFramework/GameModeBase.h"
#include "GameMode_BB.generated.h"

class UBallsWorldSubsystem;
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
	void InitBallsSubsystem();
	
	UFUNCTION()
	void InitAudioSubsystem() const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitSubsystems();
	
private:
	
	UPROPERTY()
	TObjectPtr<UBricksWallWorldSubsystem> BricksWallWorldSubsystem;
	
	UPROPERTY()
	TObjectPtr<UScoreWorldSubsystem> ScoreWorldSubsystem;
	
	
	UPROPERTY()
	int CurrentLevel = 1;
	
public:
	
	UFUNCTION(BlueprintPure)
	int GetCurrentLevel() const;
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentLevel(int InLevel);
	
	UFUNCTION(BlueprintCallable)
	void IncrementCurrentLevel();
	
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateCurrentLevel, int, InCurrentLevel);
	UPROPERTY(BlueprintAssignable)
	FOnUpdateCurrentLevel OnUpdateCurrentLevel;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UBallsWorldSubsystem> BallsWorldSubsystem;
	
	UFUNCTION()
	void RoundFinished(ERoundFinishedID InRoundFinishedID);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveRoundFinished(ERoundFinishedID InRoundFinishedID);
	
	UFUNCTION()
	void GameFinished(EGameFinishedID InGameFinishedID);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveGameFinished(EGameFinishedID InGameFinishedID);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundFinished, ERoundFinishedID, InID);
	UPROPERTY(BlueprintAssignable)
	FOnRoundFinished OnRoundFinished;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameFinished, EGameFinishedID, InID);
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameFinished OnGameFinished;
	
	UFUNCTION(BlueprintPure)
	int GetLifePoint() const;
	
	UFUNCTION(BlueprintCallable)
	void SetLifePoint(int InLifePoint);
	
	UFUNCTION(BlueprintCallable)
	void DecrementLifePoint();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveUpdateLifePoint();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateLifePoint, int, InLifePoint);
	UPROPERTY(BlueprintAssignable)
	FOnUpdateLifePoint OnUpdateLifePoint;
	
private:
	
	UPROPERTY()
	int CurrentLifePoint = 3;
	
	UFUNCTION()
	void ReactOnOneBrickDestruct(ABrick_Base* InBrick);
	
	UFUNCTION()
	void ReactOnOneBrickBounced(ABrick_Base* InBrick);
	
	UFUNCTION()
	void ReactOnOneBallDestruct(ABall_BB* InBall);
	
public:
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveOneBrickDestruct(ABrick_Base* InBrick);
	
public:
	
	UFUNCTION(BlueprintCallable)
	ABall_BB* StartGame(bool InSpawnFirstBall = true, bool InDirectlyInitFirstBall = false);
	
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartGame();
	
};
