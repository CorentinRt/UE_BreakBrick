// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/StateMachine/PlayerPawnState.h"
#include "PlayerPawnState_LaunchBall.generated.h"

/**
 * 
 */
UCLASS()
class BREAKBRICK_API UPlayerPawnState_LaunchBall : public UPlayerPawnState
{
	GENERATED_BODY()
	
public:
	virtual EPlayerPawnStateID GetStateId() const override;

	virtual void StateInit(UPlayerStateMachine* InStateMachine) override;

	virtual void StateEnter(EPlayerPawnStateID PreviousState) override;

	virtual void StateExit(EPlayerPawnStateID NextState) override;

	virtual void StateTick(float DeltaTime) override;
};
