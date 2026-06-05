// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_LobbyMenu_Sub.h"
#include "CommonButtonBase.h"

#include "GameInstance/PR_GameIntance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/PR_OptionUIInterface.h"
#include "UI/PR_CreateSessionPopUp.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonListView.h"

#include "ListRow/PR_SessionDataRow.h"

void UPR_LobbyMenu_Sub::CreateSessionButtonClicked() const
{
	if (!CreateSessionPopUpWidgetClass || !PopUpStack) { return; }
	
	PopUpStack->AddWidget(CreateSessionPopUpWidgetClass);
	
	CreateSessionButton->SetIsEnabled(false);
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
	if (!GameOptionWidgetClass) { return; }
	
	if (IPR_OptionUIInterface* OptionInterface = Cast<IPR_OptionUIInterface>(GetOwningPlayer()))
	{
		OptionInterface->RequestOptionPopup(GameOptionWidgetClass);
	}
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

void UPR_LobbyMenu_Sub::AddMyCreatedSessionToList(const FOnlineSessionSettings& CreatedSettings)
{
	if (!LobbyListView) return;
	
	UPR_SessionDataRow* NewRow = NewObject<UPR_SessionDataRow>(this, UPR_SessionDataRow::StaticClass());
	if (!NewRow) return;
	
	FString DisplayRoomName;
	CreatedSettings.Get(FName("LobbyName"), DisplayRoomName);
	NewRow->RoomName = DisplayRoomName.IsEmpty() ? TEXT("My Custom Raid Room") : DisplayRoomName;
	
	NewRow->Ping = 0;
	NewRow->MaxPlayers = CreatedSettings.NumPublicConnections;
	NewRow->CurrentPlayers = 1; 
	
	LobbyListView->AddItem(NewRow);
}

void UPR_LobbyMenu_Sub::ResetCreateButton()
{
	if (!CreateSessionButton) { return; }
	CreateSessionButton->SetIsEnabled(false);
}
