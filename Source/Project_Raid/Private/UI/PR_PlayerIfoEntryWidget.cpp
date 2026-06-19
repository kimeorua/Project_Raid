// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_PlayerIfoEntryWidget.h"

#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "Components/Image.h"

#include "PlayerController/PR_LobbyPlayerController.h"
#include "UI/PR_CharacterSelect_Sub.h"
#include "PlayerState/PR_CharacterSelectState.h"

#include "Utils/LogHelper.h"

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

void UPR_PlayerIfoEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CachedPlayerController = Cast<APR_LobbyPlayerController>(GetOwningPlayer());
	
	SelectSwordShieldButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnSwordShieldButtonClicked);
	SelectDualSwordButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnDualSwordButtonClicked);
	SelectLanceButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnLanceButtonClicked);
	SelectKatanaButton->OnClicked().AddUObject(this, &UPR_PlayerIfoEntryWidget::OnKatanaButtonClicked);
}

void UPR_PlayerIfoEntryWidget::InitializeEntryData(APR_CharacterSelectState* InData, bool bIsHost)
{
	if (!InData) { return; }
	
	CachedPlayerInfoData = InData;
	
	PlayerName->SetText(FText::FromString(CachedPlayerInfoData->GetPlayerName()));
	SetWeaponIcon(CachedPlayerInfoData->GetCharacterType());
	
	bool bIsMySlot = false;
	
	if (APlayerController* MyPC = GetOwningPlayer())
	{
		bIsMySlot = (CachedPlayerInfoData->GetOwningController() == MyPC);
			
		if (!bIsMySlot && MyPC->PlayerState)
		{
			bIsMySlot = (CachedPlayerInfoData == MyPC->PlayerState);
		}
	}
	
	bool bIsReady = CachedPlayerInfoData->IsReady();
	FLinearColor Color = bIsReady ? FLinearColor::White : FLinearColor::Black;
	ReadyIcon->SetColorAndOpacity(Color);
	
	if (bIsHost)
	{
		ReadyIcon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ReadyIcon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	
	bool bShouldEnableButtons = bIsMySlot && !bIsReady;
	
	SelectSwordShieldButton->SetIsEnabled(bShouldEnableButtons);
	SelectDualSwordButton->SetIsEnabled(bShouldEnableButtons);
	SelectLanceButton->SetIsEnabled(bShouldEnableButtons);
	SelectKatanaButton->SetIsEnabled(bShouldEnableButtons);
}

UWidget* UPR_PlayerIfoEntryWidget::DownActionFocusWidget()
{
	if (UPR_CharacterSelect_Sub* ParentUI = GetTypedOuter<UPR_CharacterSelect_Sub>())
	{
		return  ParentUI->GetReadyOrStartButton();
	}
	return nullptr;
}

UWidget* UPR_PlayerIfoEntryWidget::UpActionFocusWidget()
{
	if (UPR_CharacterSelect_Sub* ParentUI = GetTypedOuter<UPR_CharacterSelect_Sub>())
	{
		return  ParentUI->GetOptionButton();
	}
	return nullptr;
}
