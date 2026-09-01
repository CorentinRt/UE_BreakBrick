// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/PlayerStateMachine.h"

#include "Player/Player_BB.h"
#include "Player/StateMachine/PlayerPawnState.h"
#include "Player/StateMachine/States/PlayerPawnState_Idle.h"
#include "Player/StateMachine/States/PlayerPawnState_LaunchBall.h"
#include "Player/StateMachine/States/PlayerPawnState_Move.h"

void UPlayerStateMachine::Init(APlayer_BB* InPawn)
{
	Pawn = InPawn;
	
	CreateObjectStates();

	InitStates();

	ChangeState(EPlayerPawnStateID::IDLE);
}

APlayer_BB* UPlayerStateMachine::GetPawn() const
{
	return Pawn;
}

void UPlayerStateMachine::ChangeState(EPlayerPawnStateID nextStateID)
{
	UPlayerPawnState* NextState = GetState(nextStateID);

	if (!NextState)
		return;

	if (CurrentState)
	{
		CurrentState->StateExit(nextStateID);
	}

	EPlayerPawnStateID previousStateID = CurrentStateID;
	CurrentStateID = nextStateID;
	CurrentState = NextState;

	if (CurrentState)
	{
		CurrentState->StateEnter(previousStateID);
	}
}

UPlayerPawnState* UPlayerStateMachine::GetState(EPlayerPawnStateID stateId)
{
	for (UPlayerPawnState* State : AllStates)
	{
		if (stateId == State->GetStateId())
		{
			return State;
		}
	}

	return nullptr;
}

void UPlayerStateMachine::Tick(float DeltaTime)
{
	if (!CurrentState)
		return;

	CurrentState->StateTick(DeltaTime);
}

UPlayerPawnState* UPlayerStateMachine::GetCurrentState() const
{
	return CurrentState;
}

EPlayerPawnStateID UPlayerStateMachine::GetCurrentStateID() const
{
	return CurrentStateID;
}

void UPlayerStateMachine::CreateObjectStates()
{
	if (!IsValid(Pawn))
		return;

	TArray<EPlayerPawnStateID> States = Pawn->PlayerStates;

	for (EPlayerPawnStateID State : States)
	{
		CreateStateById(State);
	}
}

void UPlayerStateMachine::CreateStateById(EPlayerPawnStateID stateId)
{
	if (!IsValid(Pawn))
		return;
	
	TObjectPtr<UPlayerPawnState> OutState = nullptr;

	if (Pawn->PlayerStateToEngineClass.IsEmpty() || !Pawn->PlayerStateToEngineClass.Contains(stateId))
		return;
	
	UClass* BpParentClass = Pawn->PlayerStateToEngineClass[stateId];
	
	if (!IsValid(BpParentClass))
		return;
	
	switch (stateId)
	{
		
	case EPlayerPawnStateID::NONE:
		break;
		
	case EPlayerPawnStateID::IDLE:
		OutState = NewObject<UPlayerPawnState_Idle>(this, BpParentClass);
		break;
		
	case EPlayerPawnStateID::MOVE:
		OutState = NewObject<UPlayerPawnState_Move>(this, BpParentClass);
		break;
	case EPlayerPawnStateID::LAUNCH_BALL:
		OutState = NewObject<UPlayerPawnState_LaunchBall>(this, BpParentClass);
		break;
	case EPlayerPawnStateID::LOCKED:
		break;
	default:
		break;
	}
	
	if (OutState)
	{
		AllStates.Add(OutState);
	}
}

void UPlayerStateMachine::InitStates()
{
	for (UPlayerPawnState* State : AllStates)
	{
		State->StateInit(this);
	}
}
