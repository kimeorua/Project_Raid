// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PR_CharacterSelectState.h"

#include "GameState/PR_CharacterSelectGameState.h"

#include "Net/UnrealNetwork.h"

APR_CharacterSelectState::APR_CharacterSelectState()
{
	SetPlayerName(TEXT("Player"));
	SelectedCharacter = ECharacterType::None;
	bAlwaysRelevant = true;
}

void APR_CharacterSelectState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APR_CharacterSelectState, SelectedCharacter);
}

void APR_CharacterSelectState::Server_SetCharacterType_Implementation(ECharacterType NewType)
{
	SelectedCharacter = NewType;
	
	OnRep_CharacterType();
}

void APR_CharacterSelectState::OnRep_CharacterType()
{
	if (APR_CharacterSelectGameState* GS = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState()))
	{
		GS->OnLobbyRefreshRequired.Broadcast();
	}
}
