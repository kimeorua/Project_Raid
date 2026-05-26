// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PR_OptionMenu.generated.h"

class UCommonButtonBase;
class UCommonTextBlock;
class USoundClass;
class USoundMix;
class UPR_LocalPlayerSubsystem_Option;

UCLASS()
class PROJECT_RAID_API UPR_OptionMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override; 
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> VolumeUpButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> VolumeDawnButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> VolumeText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundClass> SoundClass;
	
	float Volume = 1.0f;
	
	void VolumeUp();
	void VolumeDawn();
	void SoundMixOverride();
	void VolumeTextSetting();
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> GraphicUpButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> GraphicDawnButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> GraphicText;
	
	int GraphicLevel = 3;
	
	void GraphicUp();
	void GraphicDawn();
	void GraphicTextSetting();
	void GraphicOverride();
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> UICloseButton;
	
	void OptionWidgetClose();
	
	UPROPERTY()
	TObjectPtr<UPR_LocalPlayerSubsystem_Option> LocalPlayerSubsystem_Option;
};
