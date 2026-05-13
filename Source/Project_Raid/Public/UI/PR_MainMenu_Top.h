// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PR_MainMenu_Top.generated.h"

class UCommonActivatableWidgetStack;
class UPR_MainMenu_Sub;
class UCommonActivatableWidget;

UCLASS()
class PROJECT_RAID_API UPR_MainMenu_Top : public UCommonUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> OptionStack;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UPR_MainMenu_Sub> GameLobbyWidgetClass;
	
	void HandleOptionUIPopupRequest(TSubclassOf<UCommonActivatableWidget> OptionPopUpClass);
	
protected:
	virtual void NativeConstruct() override;
};
