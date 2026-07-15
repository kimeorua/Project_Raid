// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/PR_UIComponent_Player.h"
#include "Blueprint/UserWidget.h"

#include "Character/PR_BaseCharacter.h"
#include "UI/PlayerHUD/PR_PlayerHUD.h"

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
	
	if (!HUD_Player)
	{
		if (!OwnerCharacter) { return; }
		APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());

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
}
