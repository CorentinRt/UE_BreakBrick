// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioSubsystemBB.generated.h"

class UGameSettings_BB;
/**
 * 
 */
UCLASS()
class BREAKBRICK_API UAudioSubsystemBB : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void InitAudioSubsystem();
	
	UFUNCTION(BlueprintCallable)
	void SetAudioClassVolume(EAudioClassID InAudioClassID, float InVolume);
	
private:
	UFUNCTION()
	const UGameSettings_BB* GetGameSettings() const;
	
	UFUNCTION()
	bool SetupAudioClassMix();
	
	UFUNCTION()
	USoundClass* GetSoundClass(EAudioClassID InAudioClassID) const;
	
	bool bIsInit = false;
	
	UPROPERTY()
	const UGameSettings_BB* GameSettings;
	
	UPROPERTY()
	USoundMix* SoundMix;
	
	UPROPERTY()
	USoundClass* MasterClass;
	
	UPROPERTY()
	USoundClass* MusicClass;
	
	UPROPERTY()
	USoundClass* SFXClass;
	
	UPROPERTY()
	USoundClass* AmbianceClass;
	
	UPROPERTY()
	USoundClass* UIClass;
};
