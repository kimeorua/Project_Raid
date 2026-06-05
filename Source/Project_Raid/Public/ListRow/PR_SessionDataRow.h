// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OnlineSessionSettings.h"
#include "PR_SessionDataRow.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECT_RAID_API UPR_SessionDataRow : public UObject
{
	GENERATED_BODY()
public:
	// UI에 출력할 실제 데이터들
	FString RoomName;
	int32 CurrentPlayers;
	int32 MaxPlayers;
	int32 Ping;
	
	FOnlineSessionSearchResult SearchResult;
};
