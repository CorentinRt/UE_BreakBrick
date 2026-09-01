// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "PlayerSettings_BB.generated.h"

class UInputMappingContext;
class UPlayerActions_BB;
/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Player Settings BB"))
class BREAKBRICK_API UPlayerSettings_BB : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, Category="Inputs")
	TSoftObjectPtr<UPlayerActions_BB> ActionsDatas;
	
	UPROPERTY(Config, EditAnywhere, Category="Inputs")
	TSoftObjectPtr<UInputMappingContext> PlayerMappingContext;
};
