// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD/PR_PlayerHUD.h"

#include "Components/VerticalBox.h"
#include "GameFramework/GameState.h"

#include "UI/PlayerHUD/PR_ProgressBar.h"

void UPR_PlayerHUD::UpdateHPBar_Owner(float NewPercent) const
{
	if (!Player_HP_Bar) { return; }
	
	Player_HP_Bar->SetPercent(NewPercent);
}

void UPR_PlayerHUD::CreateOtherPlayerBar(APlayerState* PS)
{
	AGameState* GameState = Cast<AGameState>(GetWorld()->GetGameState());
	if (!GameState) { return; }
	
	APlayerController* PC = GetOwningPlayer();
	
	if (PartySlotMap.Contains(PS)) {return; }
	
	int32 MaxOtherSlots = FMath::Max(0, GameState->PlayerArray.Num() - 1);
	
	if (OtherPlayerBox->GetChildrenCount() >= MaxOtherSlots) { return; }
	
	if (UUserWidget* OthersBar = CreateWidget<UUserWidget>(PC, OtherHPBar))
	{
		OtherPlayerBox->AddChild(OthersBar);
		PartySlotMap.Add(PS, OthersBar);
	}
}

void UPR_PlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();
}
