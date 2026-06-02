// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PR_LobbyMenu.generated.h"

class UCommonActivatableWidgetStack;
class UPR_LobbyMenu_Sub;
class UCommonActivatableWidget;

UCLASS()
class PROJECT_RAID_API UPR_LobbyMenu : public UCommonUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> MenuStack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> OptionStack;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UPR_LobbyMenu_Sub> LobbyMenuClass;
	
protected:
	virtual void NativeConstruct() override;
};
