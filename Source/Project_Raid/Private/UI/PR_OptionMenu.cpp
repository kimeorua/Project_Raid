// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_OptionMenu.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"

void UPR_OptionMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	LocalPlayerSubsystem_Option = LocalPlayer->GetSubsystem<UPR_LocalPlayerSubsystem_Option>();
	
	UICloseButton->OnClicked().AddUObject(this, &ThisClass::OptionWidgetClose);
	
	VolumeUpButton->OnClicked().AddUObject(this, &ThisClass::VolumeUp);
	VolumeDawnButton->OnClicked().AddUObject(this, &ThisClass::VolumeDawn);
	
	GraphicUpButton->OnClicked().AddUObject(this, &ThisClass::GraphicUp);
	GraphicDawnButton->OnClicked().AddUObject(this, &ThisClass::GraphicDawn);
	
	VolumeTextSetting();
	
	if (UGameUserSettings* GSettings = UGameUserSettings::GetGameUserSettings())
	{
		GraphicLevel = GSettings->GetOverallScalabilityLevel();
	}
	GraphicTextSetting();
}
UWidget* UPR_OptionMenu::NativeGetDesiredFocusTarget() const
{
	return  IsValid(VolumeUpButton) ? VolumeUpButton : Super::NativeGetDesiredFocusTarget();
}

void UPR_OptionMenu::SoundMixOverride()
{
	if (!LocalPlayerSubsystem_Option) { return;}
	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), LocalPlayerSubsystem_Option->GetGameSoundMix(), SoundClass, Volume, 1.0f, 0.0f, true);
}

void UPR_OptionMenu::VolumeTextSetting()
{
	int32 TargetVolumeInt = FMath::RoundToInt(Volume * 100.0f);
	
	FString VolumeStr = FString::Printf(TEXT("Sound : %d %%"), TargetVolumeInt);
	
	VolumeText->SetText(FText::FromString(VolumeStr));
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

void UPR_OptionMenu::GraphicUp()
{
	GraphicLevel += 1;
	GraphicLevel = FMath::Clamp(GraphicLevel, 0, 4);
	
	GraphicTextSetting();
	GraphicOverride();
}

void UPR_OptionMenu::GraphicDawn()
{
	GraphicLevel -= 1;
	GraphicLevel = FMath::Clamp(GraphicLevel, 0, 4);
	
	GraphicTextSetting();
	GraphicOverride();
}

void UPR_OptionMenu::GraphicTextSetting()
{
	FString GraphicStr;
	
	switch (GraphicLevel)
	{
		case 0:
		GraphicStr = TEXT("Low");
		break;
		
		case 1:
		GraphicStr = TEXT("Medium");
		break;
		
		case 2:
		GraphicStr = TEXT("High");
		break;
		
		case 3:
		GraphicStr = TEXT("Epic");
		break;
		
		case 4:
		GraphicStr = TEXT("Cinematic");
		break;
		
		default:
		GraphicStr = TEXT("High");
		break;
	}
	GraphicText->SetText(FText::FromString(GraphicStr));
}

void UPR_OptionMenu::GraphicOverride()
{
	UGameUserSettings::GetGameUserSettings()->SetOverallScalabilityLevel(GraphicLevel);
	UGameUserSettings::GetGameUserSettings()->ApplySettings(true);
}

void UPR_OptionMenu::OptionWidgetClose()
{
	DeactivateWidget();
}