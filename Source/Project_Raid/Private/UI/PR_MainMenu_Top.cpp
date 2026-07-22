// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_MainMenu_Top.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "UI/PR_MainMenu_Sub.h"
#include "Subsystem/PR_LocalPlayerSubsystem_Option.h"
#include "UI/PR_LobbyMenu_Sub.h"
#include "GameInstance/PR_GameInstance.h"

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

UPR_LobbyMenu_Sub* UPR_MainMenu_Top::GetLobbySubWidget() const
{
	if (!MenuStack) return nullptr;
	return Cast<UPR_LobbyMenu_Sub>(MenuStack->GetActiveWidget());
}

UPR_MainMenu_Sub* UPR_MainMenu_Top::GetMainMenuSubWidget() const
{
	if (!MenuStack) return nullptr;
	return Cast<UPR_MainMenu_Sub>(MenuStack->GetActiveWidget());
}

void UPR_MainMenu_Top::NativeConstruct()
{
	Super::NativeConstruct();
	
	UPR_GameInstance* GI = Cast<UPR_GameInstance>(GetGameInstance());
	
	if (GI && GI->CheckSkipLogin())
	{
		GI->ResetSkipLogin();
		
		if (IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
		{
			IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
			if (SessionInterface.IsValid())
			{
				SessionInterface->DestroySession(NAME_GameSession);
			}
		}
		
		PopUpLobbyUI();
	}
	else
	{
		MenuStack->AddWidget<UPR_MainMenu_Sub>(GameMainMenuWidgetClass);
	}
	
	ULocalPlayer* LocalPlayer = GetOwningLocalPlayer();
	UPR_LocalPlayerSubsystem_Option* LocalPlayerSubsystem_Option = LocalPlayer->GetSubsystem<UPR_LocalPlayerSubsystem_Option>();
	LocalPlayerSubsystem_Option->RefreshVolume();
}
