// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "PR_LobbyMenu_Sub.generated.h"

class UCommonButtonBase;
class UPR_GameInstance;
class UCommonActivatableWidgetStack;
class UCommonListView;
class FOnlineSessionSettings;
class UPR_CreateSessionPopUp;

UCLASS()
class PROJECT_RAID_API UPR_LobbyMenu_Sub : public UCommonActivatableWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> CreateSessionButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> OptionButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> ExitButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonButtonBase> RefreshButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonActivatableWidgetStack> PopUpStack;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCommonListView> LobbyListView;
	
	UPROPERTY()
	TObjectPtr<UPR_GameInstance> GameInstance;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UCommonActivatableWidget> GameOptionWidgetClass;
	
	UPROPERTY(EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UCommonActivatableWidget> CreateSessionPopUpWidgetClass;
	
	UFUNCTION()
	void CreateSessionButtonClicked();
	
	UFUNCTION()
	void ExitButtonClicked() const;
	
	UFUNCTION()
	void OptionButtonClicked() const;
	
	UFUNCTION()
	void RefreshButtonClicked();
	
protected:
	virtual void NativeConstruct() override;
	virtual UWidget* NativeGetDesiredFocusTarget() const override;
	
public:
	UFUNCTION()
	void ResetCreateButton();
	
	void UpdateSessionListView(const TArray<FOnlineSessionSearchResult>& SearchResults);
	
	void ResetAllButtons();
	
	void ButtonsDisable();
	
	UPR_CreateSessionPopUp* GetPopUp() const;
};
