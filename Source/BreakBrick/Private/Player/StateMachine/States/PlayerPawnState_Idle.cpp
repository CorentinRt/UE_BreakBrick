// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/States/PlayerPawnState_Idle.h"

EPlayerPawnStateID UPlayerPawnState_Idle::GetStateId() const
{
	return EPlayerPawnStateID::IDLE;
}

void UPlayerPawnState_Idle::StateInit(UPlayerStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
	
}

void UPlayerPawnState_Idle::StateEnter(EPlayerPawnStateID PreviousState)
{
	Super::StateEnter(PreviousState);
	
}

void UPlayerPawnState_Idle::StateExit(EPlayerPawnStateID NextState)
{
	Super::StateExit(NextState);
	
}

void UPlayerPawnState_Idle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
}
