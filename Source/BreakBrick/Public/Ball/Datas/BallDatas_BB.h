// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BallDatas_BB.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UBallDatas_BB : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float InitialSpeed = 1200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxSpeed = 1200.f;
	
};
