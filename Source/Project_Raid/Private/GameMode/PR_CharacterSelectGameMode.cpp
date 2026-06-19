// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PR_CharacterSelectGameMode.h"

APR_CharacterSelectGameMode::APR_CharacterSelectGameMode()
{
	bIsLobbyLocked = false;
}

void APR_CharacterSelectGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	
	if (bIsLobbyLocked)
	{
		ErrorMessage = TEXT("Lobby_Is_Already_Closed");
		return;
	}
}

void APR_CharacterSelectGameMode::LockLobby()
{
	bIsLobbyLocked = true;
}
