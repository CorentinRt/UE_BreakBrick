// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Player_BB.h"

#include "BreakBrick.h"
#include "EnhancedInputComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Player/StateMachine/PlayerStateMachine.h"


// Sets default values
APlayer_BB::APlayer_BB()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	
	SetRootComponent(BoxCollision);
	PlayerMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void APlayer_BB::BeginPlay()
{
	Super::BeginPlay();

	
	if (bAutoInit)
	{
		InitPlayerPawn();
	}
}

// Called every frame
void APlayer_BB::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TickStateMachine(DeltaTime);
}

// Called to bind functionality to input
void APlayer_BB::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	BindEventActions();
}

TObjectPtr<UPlayerDatas_BB> APlayer_BB::GetPlayerDatas() const
{
	return Datas;
}

TObjectPtr<APlayerController_BB> APlayer_BB::GetPlayerController() const
{
	return PlayerController;
}

void APlayer_BB::InitPlayerPawn()
{
	CreateStateMachine();
	InitStateMachine();
	
	UE_LOGFMT(LogBreakBrick, Log, "Init Player Character BB");
}

void APlayer_BB::CreateStateMachine()
{
	StateMachine = NewObject<UPlayerStateMachine>(this);
}

void APlayer_BB::InitStateMachine()
{
	if (!IsValid(StateMachine))
		return;
		
	StateMachine->Init(this);
}

void APlayer_BB::TickStateMachine(float DeltaTime) const
{
	if (!IsValid(StateMachine))
		return;

	StateMachine->Tick(DeltaTime);
}

void APlayer_BB::RightMovementAction(float InValue, float InScale)
{
	AddMovementInput(GetActorRightVector(), InValue * InScale);
}

void APlayer_BB::BindEventActions()
{
	if (!IsValid(Controller))
		return;

	PlayerController = Cast<APlayerController_BB>(Controller);

	if (!IsValid(PlayerController))
		return;

	PlayerController->OnPlayerMoveXInput.AddDynamic(this, &APlayer_BB::ReceiveMoveXInput);
	PlayerController->OnPlayerLaunchBallInput.AddDynamic(this, &APlayer_BB::ReceiveLaunchInput);
}

void APlayer_BB::ReceiveMoveXInput(float InInput)
{
	OnPlayerMoveXAction.Broadcast(InInput);
}

void APlayer_BB::ReceiveLaunchInput(bool InInput)
{
	OnPlayerLaunchBallAction.Broadcast(InInput);
}

