// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_CharacterSelect_Top.h"

#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonActivatableWidget.h"

#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"
#include "UI/PR_CharacterSelect_Sub.h"

void UPR_CharacterSelect_Top::NativeConstruct()
{
	Super::NativeConstruct();
	
	CharacterSelect_SubUI = CharacterSelectMenuStack->AddWidget<UPR_CharacterSelect_Sub>(CharacterSelectWidgetClass);
	
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	UPR_LocalPlayerSubsystem_Option* LocalPlayerSubsystem_Option = LocalPlayer->GetSubsystem<UPR_LocalPlayerSubsystem_Option>();
	LocalPlayerSubsystem_Option->RefreshVolume();
}

void UPR_CharacterSelect_Top::PushOptionWidget(TSubclassOf<UCommonActivatableWidget> OptionUIClass)
{
	if (!OptionStack || !OptionUIClass) { return;}
	
	OptionStack->AddWidget(OptionUIClass);
}

UPR_CharacterSelect_Sub* UPR_CharacterSelect_Top::GetCharacterSelect_Sub() const
{
	return  CharacterSelect_SubUI ? CharacterSelect_SubUI : nullptr;
}
