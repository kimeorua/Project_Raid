// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD/PR_PlayerHUD.h"

#include "UI/PlayerHUD/PR_ProgressBar.h"

void UPR_PlayerHUD::UpdateHPBar_Owner(float NewPercent) const
{
	if (!Player_HP_Bar) { return; }
	
	Player_HP_Bar->SetPercent(NewPercent);
}

void UPR_PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}
