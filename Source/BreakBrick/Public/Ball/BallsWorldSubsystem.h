// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BallsWorldSubsystem.generated.h"

class ABallSpawnPoint;
class ABall_BB;
class UBricksWall_Datas;
/**
 * 
 */
UCLASS()
class BREAKBRICK_API UBallsWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
	
public:
	
	UFUNCTION()
	void Init();
	
	UFUNCTION(BlueprintCallable)
	void ClearBalls();
	
	UFUNCTION()
	void LoadBricksWallDatasFromConfig();
	
	UFUNCTION()
	void FindExistingBalls();
	
	UFUNCTION()
	void FindBallsSpawnPoint();
	
	UFUNCTION(BlueprintCallable)
	ABall_BB* CreateNewBall(bool InDirectlyInitBall = true);
	
	UFUNCTION()
	void ReceiveBallDestruct(ABall_BB* InBall);
	
	UFUNCTION()
	void ReceiveBallBounced(ABall_BB* InBall);
	
	UFUNCTION(BlueprintCallable)
	bool AllBricksAreDestroyed();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOneBallDestruct, ABall_BB*, InBall);
	FOnOneBallDestruct OnOneBallDestruct;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOneBallBounced, ABall_BB*, InBall);
	FOnOneBallBounced OnOneBallBounced;
	
	
	UFUNCTION(BlueprintPure)
	FVector GetBallSpawnPointLocation() const;
	
private:
	
	UFUNCTION()
	void BindBallListeners(ABall_BB* InBall);
	
	UFUNCTION()
	void UnbindBallListeners(ABall_BB* InBall);
	
	UPROPERTY()
	TArray<ABall_BB*> AllBalls;
	
	UPROPERTY()
	TObjectPtr<ABallSpawnPoint> BallSpawnPoint;
	
	UPROPERTY()
	FName BallTag = "Ball";
	
	UPROPERTY()
	FName BallSpawnPointTag = "BallSpawnPoint";
	
	UPROPERTY()
	TObjectPtr<UBricksWall_Datas> Datas;
	
};
