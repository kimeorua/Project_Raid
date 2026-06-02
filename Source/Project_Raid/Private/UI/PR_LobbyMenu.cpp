// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_LobbyMenu.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"
#include "UI/PR_LobbyMenu_Sub.h"

void UPR_LobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	MenuStack->AddWidget<UPR_LobbyMenu_Sub>(LobbyMenuClass);
	
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	UPR_LocalPlayerSubsystem_Option* LocalPlayerSubsystem_Option = LocalPlayer->GetSubsystem<UPR_LocalPlayerSubsystem_Option>();
	LocalPlayerSubsystem_Option->RefreshVolume();
}
