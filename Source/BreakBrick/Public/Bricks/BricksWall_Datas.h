// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrickID.h"
#include "Engine/DataAsset.h"
#include "BricksWall_Datas.generated.h"

class ABall_BB;
class ABrick_Base;

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UBricksWall_Datas : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bricks Wall")
	float XSpaceBetween = 100.f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bricks Wall")
	float YSpaceBetween = 100.f;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bricks Wall")
	int TotalX = 5;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bricks Wall")
	int TotalY = 7;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Bricks BP Classes")
	TMap<EBrickID, TSubclassOf<ABrick_Base>> BricksIdToSubClasses;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Balls")
	TSubclassOf<ABall_BB> BallSubclass;
	
};
