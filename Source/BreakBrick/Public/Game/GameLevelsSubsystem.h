// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameLevelsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UGameLevelsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OpenMainGameLevel();
	
	UFUNCTION(BlueprintCallable)
	void OpenMainMenuLevel();
	
	UFUNCTION(BlueprintCallable)
	void OpenLevelBB(TSoftObjectPtr<UWorld> InWorld);
};
