// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RoundFinishedID.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERoundFinishedID : uint8
{
	ALL_BRICKS_DESTROYED = 0,
	ALL_BALLS_DESTROYED = 1
};
