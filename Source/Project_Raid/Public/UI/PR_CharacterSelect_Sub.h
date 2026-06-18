// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PR_CharacterSelect_Sub.generated.h"


class UCommonButtonBase;
class UCommonActivatableWidget;
class UCommonListView;
class UPR_PlayerIfoEntryWidget;
class UVerticalBox;

UCLASS()
class PROJECT_RAID_API UPR_CharacterSelect_Sub : public UCommonActivatableWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> OptionButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ExitButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ReadyButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> StartButton;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UCommonActivatableWidget> GameOptionWidgetClass;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> PlayerInfoList;
	
	UFUNCTION()
	void ExitButtonClicked() const;
	
	UFUNCTION()
	void OptionButtonClicked() const;
	
	UPROPERTY()
	TArray<UPR_PlayerIfoEntryWidget*> ActiveEntryWidgets;
	
	UPROPERTY(EditAnywhere, Category = "UI", meta=(AllowPrivateAccess=true))
	TSubclassOf<UPR_PlayerIfoEntryWidget> EntryWidgetClass;
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
public:
	UFUNCTION()
	void UpdatePlayerInfoList();
	
	UWidget* GetReadyOrStartButton();
	UWidget* GetOptionButton();
};
