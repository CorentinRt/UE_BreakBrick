// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/StateMachine/States/PlayerPawnState_Move.h"

#include "Player/Player_BB.h"
#include "Player/Datas/PlayerDatas_BB.h"

EPlayerPawnStateID UPlayerPawnState_Move::GetStateId() const
{
	return EPlayerPawnStateID::MOVE;
}

void UPlayerPawnState_Move::StateInit(UPlayerStateMachine* InStateMachine)
{
	Super::StateInit(InStateMachine);
	
}

void UPlayerPawnState_Move::StateEnter(EPlayerPawnStateID PreviousState)
{
	Super::StateEnter(PreviousState);
	
	GEngine->AddOnScreenDebugMessage(
		-1,
		1.f,
		FColor::Yellow,
		TEXT("State Enter : Move")
		);
	
	MoveDir = 0.f;
	
	if (IsValid(Pawn))
	{
		Pawn->OnPlayerMoveXAction.AddDynamic(this, &UPlayerPawnState_Move::OnMove);
	}
	
}

void UPlayerPawnState_Move::StateExit(EPlayerPawnStateID NextState)
{
	Super::StateExit(NextState);
	
	if (IsValid(Pawn))
	{
		Pawn->OnPlayerMoveXAction.RemoveDynamic(this, &UPlayerPawnState_Move::OnMove);
	}
}

void UPlayerPawnState_Move::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	if (IsValid(Pawn->GetPlayerDatas()))
	{
		UpdatePlayerMovementsX(MoveDir, Pawn->GetPlayerDatas()->MovementSpeed);
	}
	
}

void UPlayerPawnState_Move::OnMove(float InMoveValue)
{
	MoveDir = InMoveValue;
	
	MoveDir = FMath::Clamp(MoveDir, -1.f, 1.f);
	
	if (FMath::Abs(MoveDir) >= 0.1f)
		return;
	
	ChangeState(EPlayerPawnStateID::IDLE);
}
