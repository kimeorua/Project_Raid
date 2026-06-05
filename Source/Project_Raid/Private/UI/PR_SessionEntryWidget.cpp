// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_SessionEntryWidget.h"
#include "ListRow/PR_SessionDataRow.h"
#include "CommonTextBlock.h"

void UPR_SessionEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	UPR_SessionDataRow* SessionData = Cast<UPR_SessionDataRow>(ListItemObject);
	if (!SessionData) return;
	
	RoomNameText->SetText(FText::FromString(SessionData->RoomName));
	PingText->SetText(FText::FromString(FString::FromInt(SessionData->Ping) + TEXT("ms")));
    
	FString PlayerCountStr = FString::Printf(TEXT("%d / %d"), SessionData->CurrentPlayers, SessionData->MaxPlayers);
	PlayerCountText->SetText(FText::FromString(PlayerCountStr));
}
