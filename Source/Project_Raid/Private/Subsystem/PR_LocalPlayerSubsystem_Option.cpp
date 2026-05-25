// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundMix.h"

void UPR_LocalPlayerSubsystem_Option::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (SoundMixClass == nullptr)
	{
		SoundMixClass = Cast<USoundMix>(StaticLoadObject(USoundMix::StaticClass(), nullptr, TEXT("/Game/Games/CommonUI/Sound/SCM_GameSound.SCM_GameSound")));
	}
	
	if (SoundMixClass)
	{
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
