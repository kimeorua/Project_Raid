// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PR_RaidGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

APR_RaidGameMode::APR_RaidGameMode()
{
	CurrentPlayerCount = 1;
}

void APR_RaidGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	ErrorMessage = TEXT("Raid_Stage_Does_Not_Allow_Join_In_Progress");
	return;
}

AActor* APR_RaidGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	FName TargetTag = FName(*FString::Printf(TEXT("Spawn_%d"), CurrentPlayerCount));
    
	APlayerStart* FoundStart = nullptr;
	
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* PlayerStart = *It;
		if (PlayerStart && PlayerStart->PlayerStartTag == TargetTag)
		{
			FoundStart = PlayerStart;
			break;
		}
	}

	CurrentPlayerCount++;

	return FoundStart ? FoundStart : Super::ChoosePlayerStart_Implementation(Player);
}