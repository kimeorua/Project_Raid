// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/PR_UIComponent_Player.h"

#include "AbilitySystemGlobals.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameState.h"

#include "Character/PR_BaseCharacter.h"
#include "GameFramework/PlayerState.h"
#include "UI/PlayerHUD/PR_PlayerHUD.h"
#include "GAS/AttributeSet/PR_BasicAttributeSet.h"
#include "GameState/PR_GameState_BattelState.h"
#include "Utils/LogHelper.h"

UPR_UIComponent_Player::UPR_UIComponent_Player()
{
}

void UPR_UIComponent_Player::BeginPlay()
{
	Super::BeginPlay();
}

void UPR_UIComponent_Player::InitComponent()
{
	Super::InitComponent();
	APlayerController* LocalPC = Cast<APlayerController>(OwnerCharacter->GetController());
	
	if (!HUD_Player)
	{
		if (!OwnerCharacter) { return; }

		if (LocalPC && LocalPC->IsLocalController())
		{
			if (!HUDClass) { return; }

			UUserWidget* HUD = CreateWidget<UUserWidget>(LocalPC, HUDClass);
			if (!HUD) { return; }

			HUD_Player = Cast<UPR_PlayerHUD>(HUD);
			if (!HUD_Player) { return; }

			HUD_Player->AddToViewport();
		}
	}
	
	if (ASC && HUD_Player)
	{
		HPChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate
		(UPR_BasicAttributeSet::GetHPAttribute()).AddUObject(this, &UPR_UIComponent_Player::OnHPChanged);
		
		MaxHPChangedDelegateHandle = ASC->GetGameplayAttributeValueChangeDelegate
		(UPR_BasicAttributeSet::GetMaxHPAttribute()).AddUObject(this, &UPR_UIComponent_Player::OnMaxHPChanged);

		float CurrentHealth = ASC->GetNumericAttribute(UPR_BasicAttributeSet::GetHPAttribute());
		float CurrentMaxHealth = ASC->GetNumericAttribute(UPR_BasicAttributeSet::GetMaxHPAttribute());

		HUD_Player->UpdateHPBar_Owner(CurrentHealth / CurrentMaxHealth);
	}
	
	OtherPlayersUI_Create(LocalPC);
	
	if (APR_GameState_BattelState* GS = GetWorld() ? GetWorld()->GetGameState<APR_GameState_BattelState>() : nullptr)
	{
		GS->OnPartyHPChanged.AddDynamic(this, &UPR_UIComponent_Player::HandlePartyHPChanged);
	}
}

void UPR_UIComponent_Player::OnHPChanged(const FOnAttributeChangeData& Data)
{
	if (HUD_Player && ASC)
	{
		float MaxHP = ASC->GetNumericAttribute(UPR_BasicAttributeSet::GetMaxHPAttribute());
        
		HUD_Player->UpdateHPBar_Owner(Data.NewValue / MaxHP);
	}
}

void UPR_UIComponent_Player::OnMaxHPChanged(const FOnAttributeChangeData& Data)
{
	if (HUD_Player && ASC)
	{
		float CurrentHP = ASC->GetNumericAttribute(UPR_BasicAttributeSet::GetHPAttribute());

		HUD_Player->UpdateHPBar_Owner(CurrentHP / Data.NewValue);
	}
}

void UPR_UIComponent_Player::OtherPlayersUI_Create(APlayerController* PC)
{
	if (!HUD_Player) { return; }
	
	AGameState* GameState = Cast<AGameState>(GetWorld()->GetGameState());
	if (!GameState) { return; }
	
	APlayerState* PlayerState = OwnerCharacter ? OwnerCharacter->GetPlayerState() : nullptr;
	
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (PS == PlayerState) { continue; }
		HUD_Player->CreateOtherPlayerBar(PS);
	}
}

void UPR_UIComponent_Player::HandlePartyHPChanged(int32 TargetID, float NewPercent)
{
	if (!HUD_Player) { return; }
	HUD_Player->UpdateHPBar_Other(TargetID, NewPercent);
}