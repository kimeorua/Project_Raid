// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_LobbyMenu_Sub.h"
#include "CommonButtonBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "CommonListView.h"

#include "GameInstance/PR_GameInstance.h"
#include "Interface/PR_OptionUIInterface.h"
#include "UI/PR_CreateSessionPopUp.h"
#include "ListRow/PR_SessionDataRow.h"

void UPR_LobbyMenu_Sub::CreateSessionButtonClicked()
{
	if (!CreateSessionPopUpWidgetClass || !PopUpStack) { return; }
	
	if (UPR_CreateSessionPopUp* PopUp = Cast<UPR_CreateSessionPopUp>(PopUpStack->AddWidget(CreateSessionPopUpWidgetClass)))
	{
		PopUp->OnCanelButtonCliked.RemoveAll(this);
		PopUp->OnCanelButtonCliked.AddDynamic(this, &UPR_LobbyMenu_Sub::ResetCreateButton);
	}
	ButtonsDisable();
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

void UPR_LobbyMenu_Sub::RefreshButtonClicked()
{
	if (LobbyListView) { LobbyListView->ClearListItems(); }
	
	ButtonsDisable();
	
	GameInstance->FindSessions();
}

void UPR_LobbyMenu_Sub::ButtonsDisable()
{
	CreateSessionButton->SetIsEnabled(false);
	OptionButton->SetIsEnabled(false);
	ExitButton->SetIsEnabled(false);
	RefreshButton->SetIsEnabled(false);
}

UPR_CreateSessionPopUp* UPR_LobbyMenu_Sub::GetPopUp() const
{
	if (!PopUpStack) return nullptr;
	return Cast<UPR_CreateSessionPopUp>(PopUpStack->GetActiveWidget());
}

void UPR_LobbyMenu_Sub::NativeConstruct()
{
	Super::NativeConstruct();
	
	GameInstance = GetGameInstance<UPR_GameInstance>();
	
	CreateSessionButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::CreateSessionButtonClicked);
	ExitButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::ExitButtonClicked);
	OptionButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::OptionButtonClicked);
	RefreshButton->OnClicked().AddUObject(this, &UPR_LobbyMenu_Sub::RefreshButtonClicked);
}

UWidget* UPR_LobbyMenu_Sub::NativeGetDesiredFocusTarget() const
{
	return IsValid(CreateSessionButton) ? CreateSessionButton : Super::NativeGetDesiredFocusTarget();
}

void UPR_LobbyMenu_Sub::ResetCreateButton()
{
	if (!CreateSessionButton) { return; }
	ResetAllButtons();
	CreateSessionButton->SetFocus();
}

void UPR_LobbyMenu_Sub::UpdateSessionListView(const TArray<FOnlineSessionSearchResult>& SearchResults)
{
	if (!LobbyListView) { return; }
	
	for (const FOnlineSessionSearchResult& Result : SearchResults)
	{
		UPR_SessionDataRow* NewRow = NewObject<UPR_SessionDataRow>(this, UPR_SessionDataRow::StaticClass());
		if (!NewRow) continue;
		
		FString DisplayRoomName;
		Result.Session.SessionSettings.Get(FName("LobbyName"), DisplayRoomName);
		NewRow->RoomName = DisplayRoomName.IsEmpty() ? TEXT("Unknown Room") : DisplayRoomName;
		
		NewRow->Ping = Result.PingInMs;
		NewRow->MaxPlayers = Result.Session.SessionSettings.NumPublicConnections;
		NewRow->CurrentPlayers = NewRow->MaxPlayers - Result.Session.NumOpenPublicConnections;
		NewRow->SearchResult = Result;
		LobbyListView->AddItem(NewRow);
	}
}

void UPR_LobbyMenu_Sub::ResetAllButtons()
{
	CreateSessionButton->SetIsEnabled(true);
	OptionButton->SetIsEnabled(true);
	ExitButton->SetIsEnabled(true);
	RefreshButton->SetIsEnabled(true);
}
