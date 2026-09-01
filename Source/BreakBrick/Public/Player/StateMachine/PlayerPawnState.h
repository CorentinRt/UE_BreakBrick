// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerPawnStateID.h"
#include "UObject/Object.h"
#include "PlayerPawnState.generated.h"

class APlayerController_BB;
class APlayer_BB;
class UPlayerStateMachine;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class BREAKBRICK_API UPlayerPawnState : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPlayerPawnState();
	
	virtual EPlayerPawnStateID GetStateId() const;

	virtual void StateInit(UPlayerStateMachine* InStateMachine);

	virtual void StateEnter(EPlayerPawnStateID PreviousState);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "StateEnter"))
	void ReceiveStateEnter(EPlayerPawnStateID PreviousState);

	virtual void StateExit(EPlayerPawnStateID NextState);

	virtual void StateTick(float DeltaTime);
	

protected:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayer_BB> Pawn;

	UPROPERTY()
	TObjectPtr<APlayerController_BB> Controller;

	UPROPERTY()
	TObjectPtr<UPlayerStateMachine> StateMachine;
	
public:
	
	UFUNCTION(BlueprintCallable)
	void ChangeState(EPlayerPawnStateID NextStateID);
	
	UFUNCTION(BlueprintCallable)
	void UpdatePlayerMovementsX(const float InDir, float InMultiplier);
};
