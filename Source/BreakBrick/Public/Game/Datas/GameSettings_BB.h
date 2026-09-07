// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameSettings_BB.generated.h"

/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Game Settings BB"))
class BREAKBRICK_API UGameSettings_BB : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(Config, EditAnywhere, Category="Levels")
	TSoftObjectPtr<UWorld> MainMenuLevel;
	
	UPROPERTY(Config, EditAnywhere, Category="Levels")
	TSoftObjectPtr<UWorld> MainGameLevel;
	
	
	UPROPERTY(Config, EditAnywhere, Category="Sounds")
	TSoftObjectPtr<USoundMix> SoundMix;
	
	UPROPERTY(Config, EditAnywhere, Category="Sounds")
	TSoftObjectPtr<USoundClass> MasterClass;
	
	UPROPERTY(Config, EditAnywhere, Category="Sounds")
	TSoftObjectPtr<USoundClass> MusicClass;
	
	UPROPERTY(Config, EditAnywhere, Category="Sounds")
	TSoftObjectPtr<USoundClass> SFXClass;
	
	UPROPERTY(Config, EditAnywhere, Category="Sounds")
	TSoftObjectPtr<USoundClass> AmbianceClass;
	
	UPROPERTY(Config, EditAnywhere, Category="Sounds")
	TSoftObjectPtr<USoundClass> UIClass;
	
};
