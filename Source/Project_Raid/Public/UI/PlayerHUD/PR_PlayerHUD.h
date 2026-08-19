// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PR_PlayerHUD.generated.h"

class UVerticalBox;
class UPR_ProgressBar;
class APlayerState;
class UPR_WeaponCombatUI;
class UOverlay;

UCLASS()
class PROJECT_RAID_API UPR_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	void UpdateHPBar_Owner(float NewPercent) const;
	void UpdateSPBar_Owner(float NewPercent) const;
	
	void UpdateHPBar_Other(int32 ID, float NewPercent);
	void CreateOtherPlayerBar(APlayerState* PS);
	void ClearOtherPlayerBars();
	
	void AddCombatUI(UPR_WeaponCombatUI* InUI);
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "HUD|Widgets", meta = (BindWidget))
	TObjectPtr<UPR_ProgressBar> Player_HP_Bar;
	
	UPROPERTY(BlueprintReadOnly, Category = "HUD|Widgets", meta = (BindWidget))
	TObjectPtr<UPR_ProgressBar> Player_SP_Bar;
	
	UPROPERTY(BlueprintReadOnly, Category = "HUD|Widgets", meta = (BindWidget))
	TObjectPtr<UVerticalBox> OtherPlayerBox;
	
	UPROPERTY(BlueprintReadOnly, Category = "HUD|Widgets", meta = (BindWidget))
	TObjectPtr<UOverlay> WeaponCombatUI_Sloat;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HUD|Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPR_ProgressBar> OtherHPBar;
	
private:
	UPROPERTY()
	TMap<int32, TObjectPtr<UPR_ProgressBar>> PartySlotMap;
};