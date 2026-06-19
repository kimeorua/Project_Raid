// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PR_CharacterSelectGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_RAID_API APR_CharacterSelectGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	APR_CharacterSelectGameMode();
	
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	
	void LockLobby();

private:
	bool bIsLobbyLocked;
};
