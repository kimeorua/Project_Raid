// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/PR_UIComponent_Player.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/GameState.h"

#include "Character/PR_BaseCharacter.h"
#include "UI/PlayerHUD/PR_PlayerHUD.h"
#include "GAS/AttributeSet/PR_BasicAttributeSet.h"

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
	APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());
	
	if (!HUD_Player)
	{
		if (!OwnerCharacter) { return; }

		if (PC && OwnerCharacter->IsLocallyControlled() && PC->IsLocalController())
		{
			if (!HUDClass) { return; }

			UUserWidget* HUD = CreateWidget<UUserWidget>(PC, HUDClass);
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
	
	OtherPlayersUI_Create(PC);
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
	
	APlayerState* MyPlayerState = OwnerCharacter ? OwnerCharacter->GetPlayerState() : nullptr;
	
	for (APlayerState* PS : GameState->PlayerArray)
	{
		if (PS == MyPlayerState) { continue; }
		HUD_Player->CreateOtherPlayerBar(PS);
	}
}