// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_MainMenu_Sub.h"
#include "CommonButtonBase.h"

#include "GameInstance/PR_GameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/PR_OptionUIInterface.h"


void UPR_MainMenu_Sub::LoginButtonClicked() const
{
	if (!GameInstance) { return;}
	LoginButton->SetIsEnabled(false);
	ExitButton->SetIsEnabled(false);
	OptionButton->SetIsEnabled(false);
	
	GameInstance->Login();
}

void UPR_MainMenu_Sub::ExitButtonClicked() const
{
	if (!GameInstance) { return; }
	UKismetSystemLibrary::QuitGame(GetWorld(), GameInstance->GetFirstLocalPlayerController(), EQuitPreference::Quit, false);
}

void UPR_MainMenu_Sub::OptionButtonClicked() const
{
	if (!GameOptionWidgetClass) { return; }
	
	if (IPR_OptionUIInterface* OptionInterface = Cast<IPR_OptionUIInterface>(GetOwningPlayer()))
	{
		OptionInterface->RequestOptionPopup(GameOptionWidgetClass);
	}
}

void UPR_MainMenu_Sub::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = GetGameInstance<UPR_GameInstance>();
	
	LoginButton->OnClicked().AddUObject(this, &UPR_MainMenu_Sub::LoginButtonClicked);
	ExitButton->OnClicked().AddUObject(this, &UPR_MainMenu_Sub::ExitButtonClicked);
	OptionButton->OnClicked().AddUObject(this, &UPR_MainMenu_Sub::OptionButtonClicked);
}

UWidget* UPR_MainMenu_Sub::NativeGetDesiredFocusTarget() const
{
	return IsValid(LoginButton) ? LoginButton : Super::NativeGetDesiredFocusTarget();
}

void UPR_MainMenu_Sub::ResetButtons()
{
	LoginButton->SetIsEnabled(true);
	ExitButton->SetIsEnabled(true);
	OptionButton->SetIsEnabled(true);
}
