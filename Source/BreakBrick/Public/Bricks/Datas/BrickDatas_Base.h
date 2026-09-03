// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BrickDatas_Base.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UBrickDatas_Base : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Score")
	float ScoreOnBounced = 0.f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Score")
	float ScoreOnDestruct = 100.f;
	
};
