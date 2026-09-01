// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PlayerPawnStateID.generated.h"

/**
 * 
 */
UENUM()
enum class EPlayerPawnStateID : uint8
{
	NONE = 0,
	IDLE = 1,
	MOVE = 2,
	LAUNCH_BALL = 3,
	LOCKED = 4
};
