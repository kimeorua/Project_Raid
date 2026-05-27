// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_OptionMenu.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"
#include "SaveGame/PR_OptionSaveGame.h"

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
	
	VolumeTextSetting(LocalPlayerSubsystem_Option->GetCurrentVolume());
	
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

void UPR_OptionMenu::VolumeTextSetting(float NewVolume)
{
	int32 TargetVolumeInt = FMath::RoundToInt(NewVolume * 100.0f);
	FString VolumeStr = FString::Printf(TEXT("Sound : %d %%"), TargetVolumeInt);
	VolumeText->SetText(FText::FromString(VolumeStr));
}

void UPR_OptionMenu::VolumeUp()
{
	if (!LocalPlayerSubsystem_Option) { return; }
	
	float NewVolume = LocalPlayerSubsystem_Option->GetCurrentVolume() + 0.1f;
	NewVolume = FMath::Clamp(NewVolume, 0.0f, 1.0f);
	
	LocalPlayerSubsystem_Option->UpdateVolume(NewVolume);
	VolumeTextSetting(LocalPlayerSubsystem_Option->GetCurrentVolume());
}

void UPR_OptionMenu::VolumeDawn()
{
	if (!LocalPlayerSubsystem_Option) { return; }
	
	float NewVolume = LocalPlayerSubsystem_Option->GetCurrentVolume() - 0.1f;
	NewVolume = FMath::Clamp(NewVolume, 0.0f, 1.0f);
	
	LocalPlayerSubsystem_Option->UpdateVolume(NewVolume);
	VolumeTextSetting(LocalPlayerSubsystem_Option->GetCurrentVolume());
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
	if (UPR_OptionSaveGame* SaveGameInstance = Cast<UPR_OptionSaveGame>(UGameplayStatics::CreateSaveGameObject(UPR_OptionSaveGame::StaticClass())))
	{
		if (!LocalPlayerSubsystem_Option) { return; }
		
		SaveGameInstance->SavedVolume = LocalPlayerSubsystem_Option->GetCurrentVolume();
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("SoundSlot"), 0);
	}
	
	DeactivateWidget();
}