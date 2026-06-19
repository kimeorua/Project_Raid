// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Type/Enums/PR_Enums.h"
#include "PR_PlayerIfoEntryWidget.generated.h"

class UCommonTextBlock;
class UPR_PlayerInfoDataRow;
class UCommonButtonBase;
class UImage;
class UTexture2D;
class APR_LobbyPlayerController;
class APR_CharacterSelectState;

UCLASS()
class PROJECT_RAID_API UPR_PlayerIfoEntryWidget : public UCommonUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> PlayerName;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> SelectSwordShieldButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> SelectDualSwordButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> SelectLanceButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonButtonBase> SelectKatanaButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> SelectedWeaponIcon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> ReadyIcon;
	
	UPROPERTY()
	TObjectPtr<APR_CharacterSelectState> CachedPlayerInfoData;
	
	UPROPERTY()
	TObjectPtr<APR_LobbyPlayerController> CachedPlayerController;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Icons")
	TObjectPtr<UTexture2D> SwordShieldIcon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Icons")
	TObjectPtr<UTexture2D> DualSwordIcon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Icons")
	TObjectPtr<UTexture2D> LanceIcon;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = "Icons")
	TObjectPtr<UTexture2D> KatanaIcon;
	
	void SetWeaponIcon(ECharacterType Type);
	
	UFUNCTION()
	void OnSwordShieldButtonClicked();
	
	UFUNCTION()
	void OnDualSwordButtonClicked();
	
	UFUNCTION()
	void OnLanceButtonClicked();
	
	UFUNCTION()
	void OnKatanaButtonClicked();

protected:
	virtual void NativeConstruct() override;
	
public:
	void InitializeEntryData(APR_CharacterSelectState* Data, bool bIsHost);
	
	UFUNCTION(BlueprintPure)
	UWidget* DownActionFocusWidget();
	
	UFUNCTION(BlueprintPure)
	UWidget* UpActionFocusWidget();
};
