// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_MainMenu_Top.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "UI/PR_MainMenu_Sub.h"
#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"
#include "UI/PR_LobbyMenu_Sub.h"

void UPR_MainMenu_Top::PopUpLobbyUI() const
{
	if (!MenuStack || !GameLobbyWidgetClass) { return;}
	MenuStack->ClearWidgets();
	MenuStack->AddWidget<UPR_LobbyMenu_Sub>(GameLobbyWidgetClass);
}

void UPR_MainMenu_Top::PushOptionWidget(TSubclassOf<UCommonActivatableWidget> OptionUIClass)
{
	if (!OptionStack || !OptionUIClass) { return;}
	
	OptionStack->AddWidget(OptionUIClass);
}

void UPR_MainMenu_Top::NativeConstruct()
{
	Super::NativeConstruct();
	
	MenuStack->AddWidget<UPR_MainMenu_Sub>(GameMainMenuWidgetClass);
	
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	UPR_LocalPlayerSubsystem_Option* LocalPlayerSubsystem_Option = LocalPlayer->GetSubsystem<UPR_LocalPlayerSubsystem_Option>();
	LocalPlayerSubsystem_Option->RefreshVolume();
}
