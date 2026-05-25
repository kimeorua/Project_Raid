// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PR_OptionMenu.generated.h"

class UCommonButtonBase;
class UCommonTextBlock;
class USoundClass;
class USoundMix;

UCLASS()
class PROJECT_RAID_API UPR_OptionMenu : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> VolumeUpButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> VolumeDawnButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> VolumeText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundMix> SoundMixClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USoundClass> SoundClass;
	
	void VolumeUp();
	void VolumeDawn();
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> UICloseButton;
	
	void OptionWidgetClose();
	
	float Volume = 1.0f;
	
	void VolumeTextSetting();
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override; 
};
