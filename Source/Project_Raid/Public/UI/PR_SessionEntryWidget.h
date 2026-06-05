// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PR_SessionEntryWidget.generated.h"

class UCommonTextBlock;

UCLASS()
class PROJECT_RAID_API UPR_SessionEntryWidget : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> RoomNameText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> PingText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> PlayerCountText;
};
