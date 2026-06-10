// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PR_CharacterSelect_Sub.generated.h"


class UCommonButtonBase;
class UCommonActivatableWidget;

UCLASS()
class PROJECT_RAID_API UPR_CharacterSelect_Sub : public UCommonActivatableWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> OptionButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ExitButton;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UCommonActivatableWidget> GameOptionWidgetClass;
	
	UFUNCTION()
	void ExitButtonClicked() const;
	
	UFUNCTION()
	void OptionButtonClicked() const;
	
protected:
	virtual void NativeConstruct() override;
};
