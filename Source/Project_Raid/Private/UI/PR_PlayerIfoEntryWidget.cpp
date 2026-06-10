// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PR_PlayerIfoEntryWidget.h"

#include "CommonTextBlock.h"
#include "ListRow/PR_PlayerInfoDataRow.h"

void UPR_PlayerIfoEntryWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	CachedPlayerInfoData = Cast<UPR_PlayerInfoDataRow>(ListItemObject);
	
	if (!CachedPlayerInfoData) { return; }
	
	PlayerName->SetText(FText::FromString(CachedPlayerInfoData->PlayerName));
}
