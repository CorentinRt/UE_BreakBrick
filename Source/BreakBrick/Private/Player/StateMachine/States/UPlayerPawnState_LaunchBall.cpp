// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/States/UPlayerPawnState_LaunchBall.h"

EPlayerPawnStateID UUPlayerPawnState_LaunchBall::GetStateId() const
{
	return EPlayerPawnStateID::LAUNCH_BALL;
}

void UUPlayerPawnState_LaunchBall::StateInit(UPlayerStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
	
}

void UUPlayerPawnState_LaunchBall::StateEnter(EPlayerPawnStateID PreviousState)
{
	Super::StateEnter(PreviousState);
	
}

void UUPlayerPawnState_LaunchBall::StateExit(EPlayerPawnStateID NextState)
{
	Super::StateExit(NextState);
	
}

void UUPlayerPawnState_LaunchBall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
}
