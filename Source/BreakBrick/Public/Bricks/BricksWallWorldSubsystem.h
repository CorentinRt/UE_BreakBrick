// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "BricksWallWorldSubsystem.generated.h"

class ABrick_Base;

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UBricksWallWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void PostInitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override {return TStatId(); };
	
	UFUNCTION(BlueprintCallable)
	void Init();
	
	
	UFUNCTION(BlueprintCallable)
	void GenerateNewBricksWall();
	
	UFUNCTION(BlueprintCallable)
	ABrick_Base* CreateBrick(int InX, int InY);
	
	UFUNCTION(BlueprintCallable)
	void ReceiveBrickDestruct(ABrick_Base* InBrick);
	
	UFUNCTION(BlueprintCallable)
	void AddBrickDestructListener(ABrick_Base* InBrick);
	
	UFUNCTION(BlueprintCallable)
	void RemoveBrickDestructListener(ABrick_Base* InBrick);
	
	UFUNCTION(BlueprintCallable)
	void ClearBricksWall();
	
	UFUNCTION(BlueprintCallable)
	bool AllBricksAreDestroyed();
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOneBrickDestruct);
	FOnOneBrickDestruct OnOneBrickDestruct;
	
private:
	
	UPROPERTY()
	TArray<TObjectPtr<ABrick_Base>> AllBricks;
	
	bool bHasBeenInit = false;
};
