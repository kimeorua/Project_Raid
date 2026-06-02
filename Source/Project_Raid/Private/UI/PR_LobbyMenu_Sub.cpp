// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_LobbyMenu_Sub.h"
#include "CommonButtonBase.h"

#include "GameInstance/PR_GameIntance.h"
#include "Kismet/KismetSystemLibrary.h"

void UPR_LobbyMenu_Sub::CreateSessionButtonClicked() const
{
}

void UPR_LobbyMenu_Sub::JoinSessionButtonClicked() const
{
}

void UPR_LobbyMenu_Sub::ExitButtonClicked() const
{
	if (!GameInstance) { return; }
	UKismetSystemLibrary::QuitGame(GetWorld(), GameInstance->GetFirstLocalPlayerController(), EQuitPreference::Quit, false);
}

void UPR_LobbyMenu_Sub::OptionButtonClicked() const
{
	
}

void UPR_LobbyMenu_Sub::NativeConstruct()
{
	Super::NativeConstruct();
	
	GameInstance = GetGameInstance<UPR_GameIntance>();
	
	CreateSessionButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::CreateSessionButtonClicked);
	JoinSessionButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::JoinSessionButtonClicked);
	ExitButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::ExitButtonClicked);
	OptionButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::OptionButtonClicked);
}

UWidget* UPR_LobbyMenu_Sub::NativeGetDesiredFocusTarget() const
{
	return IsValid(CreateSessionButton) ? CreateSessionButton : Super::NativeGetDesiredFocusTarget();
}
