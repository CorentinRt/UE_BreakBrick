// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController_BB.h"
#include "GameFramework/Pawn.h"
#include "StateMachine/PlayerPawnStateID.h"
#include "Player_BB.generated.h"

class UFloatingPawnMovement;
class UPlayerStateMachine;
class UPlayerPawnState;
class UPlayerDatas_BB;
class UBoxComponent;

UCLASS()
class BREAKBRICK_API APlayer_BB : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayer_BB();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
	TObjectPtr<UPlayerDatas_BB> GetPlayerDatas() const;

	TObjectPtr<APlayerController_BB> GetPlayerController() const;

#pragma region Components
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMeshComponent> PlayerMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;
	
	
#pragma endregion
	
public:
	
	UFUNCTION(BlueprintCallable)
	void InitPlayerPawn();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAutoInit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInit = false;
	
public:
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UPlayerDatas_BB> Datas;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<APlayerController_BB> PlayerController;
	
#pragma region State Machine
	
public:
	UPROPERTY(EditAnywhere)
	TArray<EPlayerPawnStateID> PlayerStates;
	
	UPROPERTY(EditAnywhere)
	TMap<EPlayerPawnStateID, TSubclassOf<UPlayerPawnState>> PlayerStateToEngineClass;
	
protected:
	void CreateStateMachine();
	void InitStateMachine();
	void TickStateMachine(float DeltaTime) const;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UPlayerStateMachine> StateMachine;
	
#pragma endregion
	
#pragma region Movements
	
public:
	
	UFUNCTION(BlueprintCallable)
	void RightMovementAction(float InValue, float InScale);
	
#pragma endregion
	
#pragma region Actions

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMoveXAction, float, MoveXValue);
	FOnPlayerMoveXAction OnPlayerMoveXAction;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerLaunchBallAction, bool, LaunchBallValue);
	FOnPlayerLaunchBallAction OnPlayerLaunchBallAction;
	
#pragma endregion
	
#pragma region Receive Inputs
	
protected:
	UFUNCTION()
	void BindEventActions();

	UFUNCTION()
	void ReceiveMoveXInput(float InInput);

	UFUNCTION()
	void ReceiveLaunchInput(bool InInput);
	
#pragma endregion
	
};
