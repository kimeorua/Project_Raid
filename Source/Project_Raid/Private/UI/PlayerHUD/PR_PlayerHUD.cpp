// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD/PR_PlayerHUD.h"
#include "Components/VerticalBox.h"

#include "UI/PlayerHUD/PR_ProgressBar.h"
#include "Utils/LogHelper.h"

void UPR_PlayerHUD::UpdateHPBar_Owner(float NewPercent) const
{
	if (!Player_HP_Bar) { return; }
	
	Player_HP_Bar->SetPercent(NewPercent);
}

void UPR_PlayerHUD::UpdateHPBar_Other(int32 ID, float NewPercent)
{
	if (!PartySlotMap.Contains(ID)) { return; }
	
	if (UPR_ProgressBar* TargetBar = PartySlotMap.FindRef(ID))
	{
		TargetBar->SetPercent(NewPercent);
	}
}

void UPR_PlayerHUD::CreateOtherPlayerBar(APlayerState* PS)
{
	if (!PS) { return; }
	
	int32 TargetID = PS->GetPlayerId();
	
	if (TargetID == 0) { return; }
	
	if (PartySlotMap.Contains(TargetID)) { return; }

	APlayerController* PC = GetOwningPlayer();
	if (!PC || !OtherPlayerBox || !OtherHPBar) { return; }
	
	if (UPR_ProgressBar* OthersBar = CreateWidget<UPR_ProgressBar>(PC, OtherHPBar))
	{
		OtherPlayerBox->AddChild(OthersBar);
		PartySlotMap.Add(TargetID, OthersBar);
	}
}

void UPR_PlayerHUD::ClearOtherPlayerBars()
{
	if (OtherPlayerBox)
	{
		OtherPlayerBox->ClearChildren();
	}
	PartySlotMap.Empty();
}

void UPR_PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}
