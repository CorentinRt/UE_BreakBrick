// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerController_BB.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/InputDeviceSubsystem.h"
#include "GameFramework/InputSettings.h"
#include "Player/Datas/PlayerActions_BB.h"
#include "Player/Datas/PlayerSettings_BB.h"

UPlayerActions_BB* APlayerController_BB::LoadActionsDataFromConfig()
{
	const UPlayerSettings_BB* PlayerSettings = GetDefault<UPlayerSettings_BB>();

	if (!IsValid(PlayerSettings))
		return nullptr;

	return PlayerSettings->ActionsDatas.LoadSynchronous();
}

UInputMappingContext* APlayerController_BB::LoadInputMappingContextFromConfig()
{
	const UPlayerSettings_BB* PlayerSettings = GetDefault<UPlayerSettings_BB>();

	if (!IsValid(PlayerSettings))
		return nullptr;

	return PlayerSettings->PlayerMappingContext.LoadSynchronous();
}

void APlayerController_BB::SetupMappingContextIntoController() const
{
	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	
	if (!IsValid(LocalPlayer))
		return;
	
	UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	
	if (!IsValid(InputSystem) && !IsValid(PlayerInputMappingContext))
		return;
	
	InputSystem->AddMappingContext(PlayerInputMappingContext, 0);
}

void APlayerController_BB::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	PlayerActionsDatas = LoadActionsDataFromConfig();
	PlayerInputMappingContext = LoadInputMappingContextFromConfig();
	
	SetupMappingContextIntoController();
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	
	if (!IsValid(EnhancedInputComponent))
		return;
	
	BindMoveXInput(EnhancedInputComponent);
	BindLaunchBallInput(EnhancedInputComponent);
}

bool APlayerController_BB::IsUsingGamepad()
{
	ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (!IsValid(LocalPlayer))
		return false;

	UInputDeviceSubsystem* InputDeviveSubsystem = GEngine->GetEngineSubsystem<UInputDeviceSubsystem>();

	if (!IsValid(InputDeviveSubsystem))
		return false;

	FHardwareDeviceIdentifier Devive = InputDeviveSubsystem->GetMostRecentlyUsedHardwareDevice(LocalPlayer->GetPlatformUserId());

	return Devive.PrimaryDeviceType == EHardwareDevicePrimaryType::Gamepad;
}

void APlayerController_BB::MoveXInput(const FInputActionValue& InInput)
{
	OnPlayerMoveXInput.Broadcast(InInput.Get<float>());
}

void APlayerController_BB::BindMoveXInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (!IsValid(PlayerActionsDatas))
		return;
	
	EnhancedInputComponent->BindAction(
		PlayerActionsDatas->MoveXAction,
		ETriggerEvent::Started,
		this,
		&APlayerController_BB::MoveXInput
	);
	
	EnhancedInputComponent->BindAction(
		PlayerActionsDatas->MoveXAction,
		ETriggerEvent::Triggered,
		this,
		&APlayerController_BB::MoveXInput
	);
	
	EnhancedInputComponent->BindAction(
		PlayerActionsDatas->MoveXAction,
		ETriggerEvent::Completed,
		this,
		&APlayerController_BB::MoveXInput
	);
	
	EnhancedInputComponent->BindAction(
		PlayerActionsDatas->MoveXAction,
		ETriggerEvent::Canceled,
		this,
		&APlayerController_BB::MoveXInput
	);
}

void APlayerController_BB::LaunchBallInput(const FInputActionValue& InInput)
{
	OnPlayerLaunchBallInput.Broadcast(InInput.Get<bool>());
}

void APlayerController_BB::BindLaunchBallInput(UEnhancedInputComponent* EnhancedInputComponent)
{
	if (!IsValid(PlayerActionsDatas))
		return;
	
	EnhancedInputComponent->BindAction(
		PlayerActionsDatas->LaunchBallAction,
		ETriggerEvent::Started,
		this,
		&APlayerController_BB::LaunchBallInput
	);
	
	EnhancedInputComponent->BindAction(
		PlayerActionsDatas->LaunchBallAction,
		ETriggerEvent::Completed,
		this,
		&APlayerController_BB::LaunchBallInput
	);
}
