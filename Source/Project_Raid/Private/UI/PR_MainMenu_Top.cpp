// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_MainMenu_Top.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

#include "UI/PR_MainMenu_Sub.h"

void UPR_MainMenu_Top::HandleOptionUIPopupRequest(TSubclassOf<UCommonActivatableWidget> OptionPopUpClass)
{
	if (!OptionStack || !OptionPopUpClass) { return;}
	
	OptionStack->AddWidget(OptionPopUpClass);
}

void UPR_MainMenu_Top::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UPR_MainMenu_Sub* MainUI = MenuStack->AddWidget<UPR_MainMenu_Sub>(GameLobbyWidgetClass))
	{
		MainUI->OnRequestOptionPopUp.BindUObject(this, &ThisClass::HandleOptionUIPopupRequest);
	}
}
