// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "BricksWall_Settings.generated.h"

class ABrick_Base;
class UBricksWall_Datas;
/**
 * 
 */
UCLASS(Config=Game, defaultconfig, meta = (DisplayName="Bricks Wall Settings BB"))
class BREAKBRICK_API UBricksWall_Settings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(Config, EditAnywhere, Category="Datas")
	TSoftObjectPtr<UBricksWall_Datas> BricksWall_Datas;
};
