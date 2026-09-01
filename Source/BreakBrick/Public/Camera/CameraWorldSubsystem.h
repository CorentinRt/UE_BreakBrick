// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	
public:

	virtual void PostInitialize() override;

	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override {return TStatId(); };
	
	UFUNCTION(BlueprintCallable)
	void Init();
	
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ACameraActor> Camera;
	
	UPROPERTY(BlueprintReadWrite)
	FName MainCameraTag = "MainCamera";
	
private:
	
	bool bHasBeenInit = false;
	
	UFUNCTION()
	void InitMainCamera();

};
