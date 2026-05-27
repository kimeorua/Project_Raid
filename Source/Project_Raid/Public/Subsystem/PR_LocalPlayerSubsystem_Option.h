// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "PR_LocalPlayerSubsystem_Option.generated.h"

class USoundMix;
class USoundClass;

UCLASS()
class PROJECT_RAID_API UPR_LocalPlayerSubsystem_Option : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	FORCEINLINE float GetCurrentVolume() const { return CurrentVolume; }
	void UpdateVolume(float NewVolume);
	void RefreshVolume();
	
	FORCEINLINE USoundMix* GetGameSoundMix() const { return SoundMixClass; }
	
private:
	UPROPERTY()
	TObjectPtr<USoundMix> SoundMixClass;
	
	UPROPERTY()
	TObjectPtr<USoundClass> SoundClass;
	
	float CurrentVolume = 1.0f;
	const FString SaveSlotName = TEXT("SoundSlot");
};
