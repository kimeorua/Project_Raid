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

void UPR_LobbyMenu_Sub::RefreshButtonClicked() const
{
	if (LobbyListView) { LobbyListView->ClearListItems(); }
	GameInstance->FindSessions();
}

void UPR_LobbyMenu_Sub::NativeConstruct()
{
	Super::NativeConstruct();
	
	GameInstance = GetGameInstance<UPR_GameIntance>();
	
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
	CreateSessionButton->SetIsEnabled(true);
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
