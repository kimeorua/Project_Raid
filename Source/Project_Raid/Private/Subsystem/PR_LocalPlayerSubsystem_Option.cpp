// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundMix.h"
#include "SaveGame/PR_OptionSaveGame.h"
#include "Sound/SoundClass.h"

void UPR_LocalPlayerSubsystem_Option::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (SoundMixClass == nullptr)
	{
		SoundMixClass = Cast<USoundMix>(StaticLoadObject(USoundMix::StaticClass(), nullptr, TEXT("/Game/Games/CommonUI/Sound/SCM_GameSound.SCM_GameSound")));
	}
	
	if (SoundClass == nullptr)
	{
		SoundClass = Cast<USoundClass>(StaticLoadObject(USoundClass::StaticClass(), nullptr, TEXT("/Game/Games/CommonUI/Sound/SC_Master.SC_Master")));
	}
	
	if (SoundMixClass)
	{
		if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
		{
			if (UPR_OptionSaveGame* LoadedGame = Cast<UPR_OptionSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0)))
			{
				CurrentVolume = LoadedGame->SavedVolume; 
			}
		}
		UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixClass);
	}
}

void UPR_LocalPlayerSubsystem_Option::Deinitialize()
{
	Super::Deinitialize();
	
	if (SoundMixClass)
	{
		UGameplayStatics::PopSoundMixModifier(GetWorld(), SoundMixClass);
	}
}

void UPR_LocalPlayerSubsystem_Option::UpdateVolume(float NewVolume)
{
	CurrentVolume = NewVolume;
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), GetGameSoundMix(), SoundClass, CurrentVolume, 1.0f, 0.0f, true);
}

void UPR_LocalPlayerSubsystem_Option::RefreshVolume()
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), GetGameSoundMix(), SoundClass, CurrentVolume, 1.0f, 0.0f, true);
}
