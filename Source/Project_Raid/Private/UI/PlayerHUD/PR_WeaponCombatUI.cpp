// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUD/PR_WeaponCombatUI.h"

#include "Components/SizeBox.h"

void UPR_WeaponCombatUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPR_WeaponCombatUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (SizeBox)
	{
		SizeBox->SetWidthOverride(Width);
		SizeBox->SetHeightOverride(Height);
	}
}
