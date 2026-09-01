// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/PlayerPawnState.h"

#include "Player/Player_BB.h"
#include "Player/StateMachine/PlayerStateMachine.h"

UPlayerPawnState::UPlayerPawnState()
{
	
}

EPlayerPawnStateID UPlayerPawnState::GetStateId() const
{
	return EPlayerPawnStateID::NONE;
}

void UPlayerPawnState::StateInit(UPlayerStateMachine* InStateMachine)
{
	StateMachine = InStateMachine;

	if (StateMachine)
	{
		Pawn = StateMachine->GetPawn();
		
		if (IsValid(Pawn))
		{
			Controller = Pawn->GetPlayerController();
		}
		
	}
}

void UPlayerPawnState::StateEnter(EPlayerPawnStateID PreviousState)
{
	
}

void UPlayerPawnState::StateExit(EPlayerPawnStateID NextState)
{
	
}

void UPlayerPawnState::StateTick(float DeltaTime)
{
	
}

void UPlayerPawnState::ChangeState(EPlayerPawnStateID NextStateID)
{
	if (!IsValid(StateMachine))
		return;
	
	StateMachine->ChangeState(NextStateID);
}
