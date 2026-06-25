// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/PR_CharacterSelectGameState.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerController/PR_LobbyPlayerController.h"
#include "UI/PR_CharacterSelect_Top.h"
#include "UI/PR_CharacterSelect_Sub.h"
#include "GameMode/PR_CharacterSelectGameMode.h"
#include "GameInstance/PR_GameInstance.h"


#include "Utils/LogHelper.h"

void APR_CharacterSelectGameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);

	APlayerController* LocalPC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!LocalPC) { return; }

	APR_LobbyPlayerController* LobbyPC = Cast<APR_LobbyPlayerController>(LocalPC);
	if (!LobbyPC) { return; }

	UPR_CharacterSelect_Top* CharacterSelect_Top = Cast<UPR_CharacterSelect_Top>(LobbyPC->GetCharacterSelectUI());
	if (!CharacterSelect_Top) { return; }

	if (UPR_CharacterSelect_Sub* CharacterSelect_Sub = CharacterSelect_Top->GetCharacterSelect_Sub())
	{
		CharacterSelect_Sub->UpdatePlayerInfoList();
	}
	else { return; }
}

void APR_CharacterSelectGameState::RemovePlayerState(APlayerState* PlayerState)
{
	Super::RemovePlayerState(PlayerState);
}

void APR_CharacterSelectGameState::StartGame(const FString& GameLV_Name)
{
	if (!HasAuthority()) return;
	
	if (UPR_GameInstance* GI = Cast<UPR_GameInstance>(GetGameInstance()))
	{
		GI->HideSessionOnMatchStart();
	}
	
	if (UWorld* World = GetWorld())
	{
		if (AGameModeBase* GM = World->GetAuthGameMode())
		{
			GM->bUseSeamlessTravel = true;
			if (APR_CharacterSelectGameMode* PR_GM = Cast<APR_CharacterSelectGameMode>(GM))
			{
				PR_GM->LockLobby();
			}
		}
		World->ServerTravel(GameLV_Name); 
	}
}
