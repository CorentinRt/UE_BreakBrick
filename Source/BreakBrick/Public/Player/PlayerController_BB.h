// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_BB.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UPlayerActions_BB;
/**
 * 
 */
UCLASS()
class BREAKBRICK_API APlayerController_BB : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	UPlayerActions_BB* LoadActionsDataFromConfig();
	UInputMappingContext* LoadInputMappingContextFromConfig();
	
	UFUNCTION()
	void SetupMappingContextIntoController() const;
	
	UFUNCTION()
	virtual void SetupInputComponent() override;
	
	UPROPERTY()
	TObjectPtr<UInputMappingContext> PlayerInputMappingContext;
	
	UPROPERTY()
	TObjectPtr<UPlayerActions_BB> PlayerActionsDatas;
	
	UFUNCTION(BlueprintCallable)
	bool IsUsingGamepad();
	
	
public:
	
	// Move X Input
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMoveXInput, float, MoveXInput);
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPlayerMoveXInput OnPlayerMoveXInput;
	
	// Launch Ball Input
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLaunchBallInput, bool, LaunchBallInput);
	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FOnPlayerLaunchBallInput OnPlayerLaunchBallInput;
	
	
protected:
	
	// Movements Inputs
	UFUNCTION()
	void MoveXInput(const FInputActionValue& InInput);
	UFUNCTION()
	void BindMoveXInput(UEnhancedInputComponent* EnhancedInputComponent);
	
	// Look Inputs
	UFUNCTION()
	void LaunchBallInput(const FInputActionValue& InInput);
	UFUNCTION()
	void BindLaunchBallInput(UEnhancedInputComponent* EnhancedInputComponent);
	
	
};
