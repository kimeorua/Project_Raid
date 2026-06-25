// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerState/PR_PlayerState.h"

#include "Character/PR_PlayerCharacter.h"
#include "GameState/PR_CharacterSelectGameState.h"

#include "Net/UnrealNetwork.h"

APR_PlayerState::APR_PlayerState()
{
	SetPlayerName(TEXT("Player"));
	SelectedWeapon = EWeaponType::None;
	bAlwaysRelevant = true;
}

void APR_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APR_PlayerState, SelectedWeapon);
	DOREPLIFETIME(APR_PlayerState, bIsReady);
}

void APR_PlayerState::Server_SetIsReady_Implementation(bool bNewReadyState)
{
	if (bIsReady == bNewReadyState) return;
	bIsReady = bNewReadyState;
	
	OnRep_IsReady();
}

void APR_PlayerState::Server_SetCharacterType_Implementation(EWeaponType NewType)
{
	SelectedWeapon = NewType;
	
	OnRep_CharacterType();
}

void APR_PlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);
	if (APR_PlayerState* NewPlayerState = Cast<APR_PlayerState>(PlayerState))
	{
		NewPlayerState->SelectedWeapon = this->SelectedWeapon;
	}
}

void APR_PlayerState::OnRep_CharacterType()
{
	if (APR_CharacterSelectGameState* GS = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState()))
	{
		GS->OnLobbyRefreshRequired.Broadcast();
	}
	
	if (APR_PlayerCharacter* MyCharacter = Cast<APR_PlayerCharacter>(GetPawn()))
	{
		MyCharacter->InitWeaponConfiguration();
	}
}

void APR_PlayerState::OnRep_IsReady()
{
	if (APR_CharacterSelectGameState* GS = Cast<APR_CharacterSelectGameState>(GetWorld()->GetGameState()))
	{
		GS->OnLobbyRefreshRequired.Broadcast();
	}
}