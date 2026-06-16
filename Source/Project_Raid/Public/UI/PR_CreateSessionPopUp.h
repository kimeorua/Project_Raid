// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PR_CreateSessionPopUp.generated.h"

class UCommonButtonBase;
class UEditableTextBox;

DECLARE_DYNAMIC_MULTICAST_DELEGATE (FOnCanelButtonCliked);

UCLASS()
class PROJECT_RAID_API UPR_CreateSessionPopUp : public UCommonActivatableWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CreateButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CancelButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UEditableTextBox> SessionNameTextBox;
	
	UFUNCTION()
	void OnCancelButtonClicked();
	
	UFUNCTION()
	void OnCreateSessionButtonClicked();
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	virtual void NativeOnDeactivated() override;
	
public:
	FOnCanelButtonCliked OnCanelButtonCliked;
};
