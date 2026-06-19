// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PR_RaidGameMode.h"

APR_RaidGameMode::APR_RaidGameMode()
{

}

void APR_RaidGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	ErrorMessage = TEXT("Raid_Stage_Does_Not_Allow_Join_In_Progress");
	return;
}
