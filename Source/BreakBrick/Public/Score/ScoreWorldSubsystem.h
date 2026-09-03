// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ScoreWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UScoreWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void Init();
	
	UFUNCTION(BlueprintCallable)
	void ResetScore();
	
	UFUNCTION(BlueprintCallable)
	void AddScore(int InScoreToAdd);
	
	UFUNCTION(BlueprintCallable)
	void SetScore(int InScore);
	
	UFUNCTION(BlueprintPure)
	int GetScore() const;
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateScore, int, ScoreValue);
	FOnUpdateScore OnUpdateScore;
	
private:
	
	UPROPERTY()
	int CurrentScore;
	
	
	
};
