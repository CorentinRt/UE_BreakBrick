// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode_BB.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API AMainMenuGameMode_BB : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void InitMainMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveInitMainMenu();
	
private:
	
	UFUNCTION()
	void InitAudioSubsystem() const;
};
