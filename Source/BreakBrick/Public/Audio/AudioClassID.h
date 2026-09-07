// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AudioClassID.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EAudioClassID : uint8
{
	NONE = 0,
	MASTER = 1,
	SFX = 2,
	AMB = 3,
	MUSIC = 4,
	UI = 5
};
