// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/GameLevelsSubsystem.h"

#include "FCTween.h"
#include "Game/Datas/GameSettings_BB.h"
#include "Kismet/GameplayStatics.h"

void UGameLevelsSubsystem::OpenMainGameLevel()
{
	if (!IsValid(GetWorld()))
		return;
	
	const UGameSettings_BB* GameSettings = GetDefault<UGameSettings_BB>();
	
	if (!IsValid(GameSettings))
		return;
	
	OpenLevelBB(GameSettings->MainGameLevel);
}

void UGameLevelsSubsystem::OpenMainMenuLevel()
{
	if (!IsValid(GetWorld()))
		return;
	
	const UGameSettings_BB* GameSettings = GetDefault<UGameSettings_BB>();
	
	if (!IsValid(GameSettings))
		return;
	
	OpenLevelBB(GameSettings->MainMenuLevel);
}

void UGameLevelsSubsystem::OpenLevelBB(TSoftObjectPtr<UWorld> InWorld)
{
	if (InWorld.IsNull())
		return;
	
	FCTween::ClearActiveTweens();
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), InWorld);
}

