// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_SessionEntryWidget.h"
#include "ListRow/PR_SessionDataRow.h"
#include "CommonTextBlock.h"
#include "CommonButtonBase.h"

#include "GameInstance/PR_GameInstance.h"

void UPR_SessionEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	CachedSessionData = Cast<UPR_SessionDataRow>(ListItemObject);
	if (!CachedSessionData) return;
	
	RoomNameText->SetText(FText::FromString(CachedSessionData->RoomName));
	PingText->SetText(FText::FromString(FString::FromInt(CachedSessionData->Ping) + TEXT("ms")));
    
	FString PlayerCountStr = FString::Printf(TEXT("%d / %d"), CachedSessionData->CurrentPlayers, CachedSessionData->MaxPlayers);
	PlayerCountText->SetText(FText::FromString(PlayerCountStr));
}

void UPR_SessionEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	JoinButton->OnClicked().AddUObject(this, &UPR_SessionEntryWidget::OnJoinButtonClicked);
}

void UPR_SessionEntryWidget::OnJoinButtonClicked()
{
	if (!CachedSessionData) { return; }
	UPR_GameInstance* GI = Cast<UPR_GameInstance>(GetGameInstance());
	if (!GI) { return; }
	
	GI->JoinSelectedSession(CachedSessionData->SearchResult);
}
