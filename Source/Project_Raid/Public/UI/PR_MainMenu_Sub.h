// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PR_MainMenu_Sub.generated.h"

DECLARE_DELEGATE_OneParam(FOnRequestOptionPopUp, TSubclassOf<UCommonActivatableWidget>);

class UCommonButtonBase;
class UPR_GameIntance;

UCLASS()
class PROJECT_RAID_API UPR_MainMenu_Sub : public UCommonActivatableWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> LoginButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> OptionButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ExitButton;
	
	UPROPERTY()
	TObjectPtr<UPR_GameIntance> GameInstance;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UCommonActivatableWidget> GameOptionWidgetClass;
	
	UFUNCTION()
	void LoginButtonClicked() const;
	
	UFUNCTION()
	void ExitButtonClicked() const;
	
	UFUNCTION()
	void OptionButtonClicked() const;
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
public:
	FOnRequestOptionPopUp OnRequestOptionPopUp;
};
