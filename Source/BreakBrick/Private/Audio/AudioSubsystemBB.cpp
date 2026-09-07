// Fill out your copyright notice in the Description page of Project Settings.


#include "Audio/AudioSubsystemBB.h"

#include "BreakBrick.h"
#include "Audio/AudioClassID.h"
#include "Game/Datas/GameSettings_BB.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"

void UAudioSubsystemBB::InitAudioSubsystem()
{
	if (bIsInit)
		return;
	
	GameSettings = GetGameSettings();
	
	if (!IsValid(GameSettings))
	{
		UE_LOGFMT(LogBreakBrick, Error, "Error : Game settings collected by audio subsystem is not valid ! Init of Audio Subsystem won't work properly");
		return;
	}
	
	if (!SetupAudioClassMix())
	{
		UE_LOGFMT(LogBreakBrick, Error, "Error : Setup of Audio Subsystem BB failed ! Init of Audio Subsystem won't work properly");
		return;
	}
	
	MasterClass = GetSoundClass(EAudioClassID::MASTER);
	SFXClass = GetSoundClass(EAudioClassID::SFX);
	AmbianceClass = GetSoundClass(EAudioClassID::AMB);
	MusicClass = GetSoundClass(EAudioClassID::MUSIC);
	UIClass = GetSoundClass(EAudioClassID::UI);
	
	if (!IsValid(MasterClass) || !IsValid(SFXClass) || !IsValid(AmbianceClass) || !IsValid(MusicClass) || !IsValid(UIClass))
	{
		UE_LOGFMT(LogBreakBrick, Error, "Error : Setup of Audio Subsystem BB failed cause one SoundClass was null ! Init of Audio Subsystem won't work properly");
		return;
	}
	
	UE_LOGFMT(LogBreakBrick, Log, "Init Audio BB Subsystem Success !");
	
	bIsInit = true;
}


void UAudioSubsystemBB::SetAudioClassVolume(EAudioClassID InAudioClassID, float InVolume)
{
	if (!bIsInit)
	{
		UE_LOGFMT(
			LogBreakBrick, 
			Error, 
			"Error : Try to set volume of Audio EB Subsystem while subsystem is not init ! Please respect init order and set volume after susbsystem is init !"
			);
		return;
	}
	
	USoundClass* AssociatedSoundClass = GetSoundClass(InAudioClassID);
	
	if (!IsValid(AssociatedSoundClass))
		return;
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, AssociatedSoundClass, InVolume);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
}

const UGameSettings_BB* UAudioSubsystemBB::GetGameSettings() const
{
	const UGameSettings_BB* OutGameSettings = GetDefault<UGameSettings_BB>();
	
	if (!IsValid(OutGameSettings))
		return nullptr;
	
	return OutGameSettings;
}

bool UAudioSubsystemBB::SetupAudioClassMix()
{
	if (GameSettings->SoundMix.IsNull())
		return false;
	
	SoundMix = GameSettings->SoundMix.LoadSynchronous();
	
	if (!IsValid(SoundMix))
		return false;
	
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMix);
	
	return true;
}

USoundClass* UAudioSubsystemBB::GetSoundClass(EAudioClassID InAudioClassID) const
{
	USoundClass* OutSoundClass = nullptr;
	
	switch (InAudioClassID)
	{
	case EAudioClassID::NONE:
		break;
	
	case EAudioClassID::MASTER:
		if (IsValid(MasterClass))
			return MasterClass;
		
		if (!GameSettings->MasterClass.IsNull())
		{
			OutSoundClass = GameSettings->MasterClass.LoadSynchronous();
		}
		break;
		
	case EAudioClassID::SFX:
		if (IsValid(SFXClass))
			return SFXClass;
		
		if (!GameSettings->SFXClass.IsNull())
		{
			OutSoundClass = GameSettings->SFXClass.LoadSynchronous();
		}
		break;
		
	case EAudioClassID::AMB:
		if (IsValid(AmbianceClass))
			return AmbianceClass;
		
		if (!GameSettings->AmbianceClass.IsNull())
		{
			OutSoundClass = GameSettings->AmbianceClass.LoadSynchronous();
		}
		break;
		
	case EAudioClassID::MUSIC:
		if (IsValid(MusicClass))
			return MusicClass;
		
		if (!GameSettings->MusicClass.IsNull())
		{
			OutSoundClass = GameSettings->MusicClass.LoadSynchronous();
		}
		break;
		
	case EAudioClassID::UI:
		if (IsValid(UIClass))
			return UIClass;
		
		if (!GameSettings->UIClass.IsNull())
		{
			OutSoundClass = GameSettings->UIClass.LoadSynchronous();
		}
		break;
	}

	return OutSoundClass;
}