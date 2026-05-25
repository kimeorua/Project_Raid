// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_OptionMenu.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"

void UPR_OptionMenu::SoundMixOverride()
{
	if (!LocalPlayerSubsystem_Option) { return;}
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), LocalPlayerSubsystem_Option->GetGameSoundMix(), SoundClass, Volume, 1.0f, 0.0f, true);
}

void UPR_OptionMenu::VolumeUp()
{
	Volume += 0.1f;
	
	Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	
	VolumeTextSetting();
	
	SoundMixOverride();
}

void UPR_OptionMenu::VolumeDawn()
{
	Volume -= 0.1f;
	
	Volume = FMath::Clamp(Volume, 0.0f, 1.0f);
	
	VolumeTextSetting();
	
	SoundMixOverride();
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
	
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	LocalPlayerSubsystem_Option = LocalPlayer->GetSubsystem<UPR_LocalPlayerSubsystem_Option>();
	
	UICloseButton->OnClicked().AddUObject(this, &ThisClass::OptionWidgetClose);
	
	VolumeUpButton->OnClicked().AddUObject(this, &ThisClass::VolumeUp);
	VolumeDawnButton->OnClicked().AddUObject(this, &ThisClass::VolumeDawn);
	
	VolumeTextSetting();
}
UWidget* UPR_OptionMenu::NativeGetDesiredFocusTarget() const
{
	return  IsValid(VolumeUpButton) ? VolumeUpButton : Super::NativeGetDesiredFocusTarget();
}