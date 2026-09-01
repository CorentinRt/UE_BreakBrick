// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/States/PlayerPawnState_Idle.h"

#include "Player/Player_BB.h"

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
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		1.f,
		FColor::Yellow,
		TEXT("State Enter : Idle")
		);
	
	if (IsValid(Pawn))
	{
		Pawn->OnPlayerMoveXAction.AddDynamic(this, &UPlayerPawnState_Idle::OnMove);
	}
	
}

void UPlayerPawnState_Idle::StateExit(EPlayerPawnStateID NextState)
{
	Super::StateExit(NextState);
	
	if (IsValid(Pawn))
	{
		Pawn->OnPlayerMoveXAction.RemoveDynamic(this, &UPlayerPawnState_Idle::OnMove);
	}
	
}

void UPlayerPawnState_Idle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
}

void UPlayerPawnState_Idle::OnMove(float InMoveValue)
{
	if (InMoveValue == 0.0f)
		return;
	
	ChangeState(EPlayerPawnStateID::MOVE);
}
