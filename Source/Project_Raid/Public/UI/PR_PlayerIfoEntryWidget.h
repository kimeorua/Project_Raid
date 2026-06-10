// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "PR_PlayerIfoEntryWidget.generated.h"

class UCommonTextBlock;
class UPR_PlayerInfoDataRow;

UCLASS()
class PROJECT_RAID_API UPR_PlayerIfoEntryWidget : public UCommonUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> PlayerName;
	
	UPROPERTY()
	TObjectPtr<UPR_PlayerInfoDataRow> CachedPlayerInfoData;

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
};
