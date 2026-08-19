// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/UI/PR_UIComponent_Base.h"
#include "PR_UIComponent_Player.generated.h"

class UPR_PlayerHUD;
class APR_GameState_BattleState;
class APlayerState;
class UPR_WeaponCombatUI;

UCLASS()
class PROJECT_RAID_API UPR_UIComponent_Player : public UPR_UIComponent_Base
{
	GENERATED_BODY()
public:
	UPR_UIComponent_Player();
	virtual void BeginPlay() override;
	virtual void InitComponent() override;
	void CreateCombatUI(TSubclassOf<UPR_WeaponCombatUI> InWeaponCombatUI);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPR_PlayerHUD> HUDClass;
	
	UPROPERTY()
	TObjectPtr<UPR_PlayerHUD> HUD_Player;
	
	//---------------HP 변동---------------------------//
	virtual void OnHPChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxHPChanged(const FOnAttributeChangeData& Data);
	
	//---------------SP 변동---------------------------//
	virtual void OnSPChanged(const FOnAttributeChangeData& Data);
	virtual void OnMaxSPChanged(const FOnAttributeChangeData& Data);
	
	FDelegateHandle SPChangedDelegateHandle;
	FDelegateHandle MaxSPChangedDelegateHandle;
	
	UFUNCTION()
	void HandlePartyHPChanged(int32 TargetID, float NewPercent);
	
private:
	bool IsNetworkUIReady(APR_GameState_BattleState* GS, APlayerState* MyPlayerState);
	void BindPartyDelegates(APR_GameState_BattleState* GS);
	void InitializeRemotePlayersUI(APR_GameState_BattleState* GS, APlayerState* MyPlayerState);
	void TryInitializeNetworkMultiplayerUI();
};
