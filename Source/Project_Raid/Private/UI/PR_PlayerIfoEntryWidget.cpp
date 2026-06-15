// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_PlayerIfoEntryWidget.h"

#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"

#include "PlayerController/PR_LobbyPlayerController.h"
#include "ListRow/PR_PlayerInfoDataRow.h"

void UPR_PlayerIfoEntryWidget::SetWeaponIcon(ECharacterType Type)
{
	switch (Type)
	{
	case ECharacterType::None :
		SelectedWeaponIcon->SetBrushFromTexture(nullptr);
		break;
	case ECharacterType::SwordShield :
		if (!SwordShieldIcon) { return; }
		SelectedWeaponIcon->SetBrushFromTexture(SwordShieldIcon);
		break;
	case ECharacterType::DualSword :
		if (!DualSwordIcon) { return; }
		SelectedWeaponIcon->SetBrushFromTexture(DualSwordIcon);
		break;
	case ECharacterType::Lance :
		if (!LanceIcon) { return; }
		SelectedWeaponIcon->SetBrushFromTexture(LanceIcon);
		break;
	case ECharacterType::Katana :
		if (!KatanaIcon) { return; }
		SelectedWeaponIcon->SetBrushFromTexture(KatanaIcon);
		break;
	}
}

void UPR_PlayerIfoEntryWidget::OnSwordShieldButtonClicked()
{
	if (!CachedPlayerController) { return; }
	
	CachedPlayerController->RequestChangeCharacter(ECharacterType::SwordShield);
	SetWeaponIcon(ECharacterType::SwordShield);
}

void UPR_PlayerIfoEntryWidget::OnDualSwordButtonClicked()
{
	if (!CachedPlayerController) { return; }
	
	CachedPlayerController->RequestChangeCharacter(ECharacterType::DualSword);
	SetWeaponIcon(ECharacterType::DualSword);
}

void UPR_PlayerIfoEntryWidget::OnLanceButtonClicked()
{
	if (!CachedPlayerController) { return; }
	
	CachedPlayerController->RequestChangeCharacter(ECharacterType::Lance);
	SetWeaponIcon(ECharacterType::Lance);
}

void UPR_PlayerIfoEntryWidget::OnKatanaButtonClicked()
{
	if (!CachedPlayerController) { return; }
	
	CachedPlayerController->RequestChangeCharacter(ECharacterType::Katana);
	SetWeaponIcon(ECharacterType::Katana);
}

void UPR_PlayerIfoEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	CachedPlayerInfoData = Cast<UPR_PlayerInfoDataRow>(ListItemObject);
	
	if (!CachedPlayerInfoData) { return; }
	
	PlayerName->SetText(FText::FromString(CachedPlayerInfoData->PlayerName));
	SetWeaponIcon(CachedPlayerInfoData->SelectCharacterType);
	
	bool bIsMySlot = false;

	if (CachedPlayerInfoData->OwningPlayerState)
	{
		APlayerController* SlotPC = CachedPlayerInfoData->OwningPlayerState->GetPlayerController();
        
		if (SlotPC)
		{
			bIsMySlot = SlotPC->IsLocalController();
		}
		else
		{
			if (APlayerController* MyLocalPC = GetOwningPlayer())
			{
				bIsMySlot = (CachedPlayerInfoData->OwningPlayerState == MyLocalPC->GetPlayerState<APR_CharacterSelectState>());
			}
		}
	}
	
	SelectSwordShieldButton->SetIsEnabled(bIsMySlot);
	SelectDualSwordButton->SetIsEnabled(bIsMySlot);
	SelectLanceButton->SetIsEnabled(bIsMySlot);
	SelectKatanaButton->SetIsEnabled(bIsMySlot);
}

void UPR_PlayerIfoEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CachedPlayerController = Cast<APR_LobbyPlayerController>(GetOwningPlayer());
	
	SelectSwordShieldButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnSwordShieldButtonClicked);
	SelectDualSwordButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnDualSwordButtonClicked);
	SelectLanceButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnLanceButtonClicked);
	SelectKatanaButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnKatanaButtonClicked);
}
