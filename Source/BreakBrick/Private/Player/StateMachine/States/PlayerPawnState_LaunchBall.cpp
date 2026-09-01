// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/States/PlayerPawnState_LaunchBall.h"

EPlayerPawnStateID UPlayerPawnState_LaunchBall::GetStateId() const
{
	return EPlayerPawnStateID::LAUNCH_BALL;
}

void UPlayerPawnState_LaunchBall::StateInit(UPlayerStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
	
}

void UPlayerPawnState_LaunchBall::StateEnter(EPlayerPawnStateID PreviousState)
{
	Super::StateEnter(PreviousState);
	
}

void UPlayerPawnState_LaunchBall::StateExit(EPlayerPawnStateID NextState)
{
	Super::StateExit(NextState);
	
}

void UPlayerPawnState_LaunchBall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
}
