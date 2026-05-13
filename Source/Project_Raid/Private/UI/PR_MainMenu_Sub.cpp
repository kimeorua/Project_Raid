// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_MainMenu_Sub.h"
#include "CommonButtonBase.h"

#include "GameInstance/PR_GameIntance.h"
#include "Kismet/KismetSystemLibrary.h"


void UPR_MainMenu_Sub::LoginButtonClicked() const
{
	if (!GameInstance) { return;}
	
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
	OnRequestOptionPopUp.ExecuteIfBound(GameOptionWidgetClass);
}

void UPR_MainMenu_Sub::NativeConstruct()
{
	Super::NativeConstruct();
	GameInstance = GetGameInstance<UPR_GameIntance>();
	
	LoginButton->OnClicked().AddUObject(this, &UPR_MainMenu_Sub::LoginButtonClicked);
	ExitButton->OnClicked().AddUObject(this, &UPR_MainMenu_Sub::ExitButtonClicked);
	OptionButton->OnClicked().AddUObject(this, &UPR_MainMenu_Sub::OptionButtonClicked);
}

UWidget* UPR_MainMenu_Sub::NativeGetDesiredFocusTarget() const
{
	return IsValid(LoginButton) ? LoginButton : Super::NativeGetDesiredFocusTarget();
}
