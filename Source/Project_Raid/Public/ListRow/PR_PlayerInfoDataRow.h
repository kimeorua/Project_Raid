// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Type/Enums/PR_Enums.h"
#include "PlayerState/PR_CharacterSelectState.h"
#include "PR_PlayerInfoDataRow.generated.h"

UCLASS()
class PROJECT_RAID_API UPR_PlayerInfoDataRow : public UObject
{
	GENERATED_BODY()
public:
	FString PlayerName;
	
	ECharacterType SelectCharacterType;
	
	UPROPERTY()
	TObjectPtr<APR_CharacterSelectState> OwningPlayerState;
};
