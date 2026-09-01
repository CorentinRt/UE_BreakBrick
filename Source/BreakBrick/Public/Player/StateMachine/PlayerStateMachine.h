// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawnStateID.h"
#include "UObject/Object.h"
#include "PlayerStateMachine.generated.h"

class UPlayerPawnState;
class APlayer_BB;
/**
 * 
 */
UCLASS()
class BREAKBRICK_API UPlayerStateMachine : public UObject
{
	GENERATED_BODY()
	
public:

	void Init(APlayer_BB* InPawn);

	APlayer_BB* GetPawn() const;

	UFUNCTION()
	void ChangeState(EPlayerPawnStateID nextStateID);

	UPlayerPawnState* GetState(EPlayerPawnStateID stateId);

	void Tick(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	UPlayerPawnState* GetCurrentState() const;

	UFUNCTION()
	EPlayerPawnStateID GetCurrentStateID() const;


protected:
	UPROPERTY()
	TObjectPtr<APlayer_BB> Pawn;

	UPROPERTY()
	TArray<UPlayerPawnState*> AllStates;

	UPROPERTY()
	EPlayerPawnStateID CurrentStateID;

	UPROPERTY()
	TObjectPtr<UPlayerPawnState> CurrentState;

	void CreateObjectStates();

	UFUNCTION()
	void CreateStateById(EPlayerPawnStateID stateId);

	void InitStates();
};
