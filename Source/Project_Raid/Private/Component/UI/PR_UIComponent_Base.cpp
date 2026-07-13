// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/PR_UIComponent_Base.h"

#include "AbilitySystemInterface.h"
#include "Blueprint/UserWidget.h"

#include "Character/PR_BaseCharacter.h"
#include "UI/PlayerHUD/PR_PlayerHUD.h"

UPR_UIComponent_Base::UPR_UIComponent_Base()
{

}

void UPR_UIComponent_Base::BeginPlay()
{
	Super::BeginPlay();
}

void UPR_UIComponent_Base::InitComponent(APR_BaseCharacter* BaseCharacter)
{	
	if (!HUD_Player)
	{
		if (!BaseCharacter) { return; }
	
		if (IAbilitySystemInterface* ASInterface = Cast<IAbilitySystemInterface>(BaseCharacter))
		{
			ASC = ASInterface->GetAbilitySystemComponent();
		}
	
		APlayerController* PC = Cast<APlayerController>(BaseCharacter->GetController());

		if (PC && BaseCharacter->IsLocallyControlled() && PC->IsLocalController())
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