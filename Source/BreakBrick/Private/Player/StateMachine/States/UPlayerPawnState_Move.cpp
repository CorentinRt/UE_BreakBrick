// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/States/UPlayerPawnState_Move.h"

EPlayerPawnStateID UUPlayerPawnState_Move::GetStateId() const
{
	return EPlayerPawnStateID::MOVE;
}

void UUPlayerPawnState_Move::StateInit(UPlayerStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
	
}

void UUPlayerPawnState_Move::StateEnter(EPlayerPawnStateID PreviousState)
{
	Super::StateEnter(PreviousState);
	
}

void UUPlayerPawnState_Move::StateExit(EPlayerPawnStateID NextState)
{
	Super::StateExit(NextState);
	
}

void UUPlayerPawnState_Move::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
}
