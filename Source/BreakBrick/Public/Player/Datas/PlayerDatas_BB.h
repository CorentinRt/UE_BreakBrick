// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PlayerDatas_BB.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UPlayerDatas_BB : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move")
	float MovementSpeed = 300.0f;
	
	
};
