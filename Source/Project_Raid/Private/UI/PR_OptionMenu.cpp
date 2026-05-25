// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_OptionMenu.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Kismet/GameplayStatics.h"

void UPR_OptionMenu::VolumeUp()
{
	Volume += 0.1f;
	
	Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	
	VolumeTextSetting();
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixClass, SoundClass, Volume);
}

void UPR_OptionMenu::VolumeDawn()
{
	Volume -= 0.1f;
	
	Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	
	VolumeTextSetting();
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixClass, SoundClass, Volume);
}

void UPR_OptionMenu::OptionWidgetClose()
{
	DeactivateWidget();
}

void UPR_OptionMenu::VolumeTextSetting()
{
	int32 TargetVolumeInt = FMath::RoundToInt(Volume * 100.0f);
	
	FString VolumeStr = FString::Printf(TEXT("Sound : %d %%"), TargetVolumeInt);
	
	VolumeText->SetText(FText::FromString(VolumeStr));
}

void UPR_OptionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (SoundMixClass)
	{
		UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixClass);
	}
	
	UICloseButton->OnClicked().AddUObject(this, &ThisClass::OptionWidgetClose);
	
	VolumeUpButton->OnClicked().AddUObject(this, &ThisClass::VolumeUp);
	VolumeDawnButton->OnClicked().AddUObject(this, &ThisClass::VolumeDawn);
	
	VolumeTextSetting();
}
UWidget* UPR_OptionMenu::NativeGetDesiredFocusTarget() const
{
	return  IsValid(VolumeUpButton) ? VolumeUpButton : Super::NativeGetDesiredFocusTarget();
}