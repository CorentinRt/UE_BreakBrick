// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MainMenuGameMode_BB.h"

#include "Audio/AudioSubsystemBB.h"

void AMainMenuGameMode_BB::BeginPlay()
{
	Super::BeginPlay();
	
	
	InitMainMenu();
}

void AMainMenuGameMode_BB::InitMainMenu()
{
	InitAudioSubsystem();
	
	ReceiveInitMainMenu();
	
	
}

void AMainMenuGameMode_BB::InitAudioSubsystem() const
{
	UGameInstance* GameInstance = GetGameInstance();
	
	if (!IsValid(GameInstance))
		return;
	
	UAudioSubsystemBB* AudioEBSubsystem = GameInstance->GetSubsystem<UAudioSubsystemBB>();
	
	if (!IsValid(AudioEBSubsystem))
		return;
	
	AudioEBSubsystem->InitAudioSubsystem();
}
